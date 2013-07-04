#include "stdafx.h"
#include "PacketCapturer.h"

#include <assert.h>
#include <pcap.h>
#include <Packet32.h>
#include <iphlpapi.h>
#include <ntddndis.h>
#pragma comment (lib, "wpcap.lib")
#pragma comment (lib, "packet.lib")
#pragma comment (lib, "iphlpapi.lib")


static char g_pcap_errbuf[PCAP_ERRBUF_SIZE];

PacketCapturer::PacketCapturer(void)
{
	m_selcted_device = 0;
	m_handle = NULL;

	m_flag_recv = true;
	m_flag_send = true;
	m_flag_no_data = true;
}


PacketCapturer::~PacketCapturer(void)
{
	finalize();
}

PacketCapturer& PacketCapturer::instance()
{
	static PacketCapturer s_inst;
	return s_inst;
}

PacketCapturer* PacketCapturer::pointer()
{
	return &instance();
}

bool PacketCapturer::initialize()
{
	// device list
	DWORD size = 0;

	GetAdaptersInfo(NULL, &size);	// query a size.
	IP_ADAPTER_INFO* info = (IP_ADAPTER_INFO*)malloc(size);
	GetAdaptersInfo(info, &size);

	for (IP_ADAPTER_INFO* itr = info; itr; itr= itr->Next)
	{
		dev_info dev;
		dev.name = itr->AdapterName;
		dev.desc = itr->Description;

		// mac addr
		dev.mac_addr.assign(&itr->Address[0], &itr->Address[itr->AddressLength]);

		// ip list
		for (PIP_ADDR_STRING ip = &itr->IpAddressList; ip; ip= ip->Next) {
			dev.ip_list.push_back(ip->Context);
		}
		m_devices.push_back(dev);
	}
	free(info);

	
	pcap_if_t* alldevs;
	if (pcap_findalldevs(&alldevs, g_pcap_errbuf)== -1)
	{
		return false;
	};
	for (pcap_if_t* dev = alldevs; dev; dev = dev->next)
	{
		dev->description;
		for (size_t i=0; i< m_devices.size(); ++i)
		{
			dev_info& info = m_devices[i];
			//if (info.desc== dev->description)
			//{
			//	info.name = dev->name;
			//}

			char* dev_name = strchr(dev->name, '{');
			char* info_name = strchr(&info.name[0], '{');
			if (_strnicmp(dev_name, info_name, strlen(dev_name))== 0)
			{
				info.name = dev->name;
			}
		}
	}
	pcap_freealldevs(alldevs);

	return !m_devices.empty();
}

void PacketCapturer::finalize()
{
	// clear all
}

uint32 PacketCapturer::getNumDevice() const
{
	return m_devices.size();
}

const std::string& PacketCapturer::getDeviceDesc( uint32 index ) const
{
	assert (0<= index && index< m_devices.size());
	return m_devices[index].desc;
}

void PacketCapturer::setDeviceIndex( uint32 index )
{
	assert (0<= index && index< m_devices.size());
	m_selcted_device = index;
}

uint32 PacketCapturer::getDeviceIndex() const
{
	return m_selcted_device;
}

uint32 PacketCapturer::getHostIpAddr()
{
	assert (0<= m_selcted_device && m_selcted_device< m_devices.size());
	assert (m_devices[m_selcted_device].ip_list.size());
	return m_devices[m_selcted_device].ip_list[0];
}

std::vector<uint8>& PacketCapturer::getHostMacAddr()
{
	assert (0<= m_selcted_device && m_selcted_device< m_devices.size());
	return m_devices[m_selcted_device].mac_addr;
}

void PacketCapturer::handle_open()
{
	if (m_handle != NULL)
	{
		handle_close();
	}

	if (m_devices.empty()) 
	{
		// not initialized.
		return;
	}
	if (m_selcted_device< 0 || m_selcted_device>= m_devices.size())
	{
		// invalidate device index.
		return;
	}
	
	pcap_t* handle = pcap_open_live(
		m_devices[m_selcted_device].name.c_str(),		// name of the device
		65536,											// portion of the packet to capture.
		// 65536 grants that the whole packet will be captured on all the MACs.
		1,												// promiscuous mode
		1000,											// read timeout
		g_pcap_errbuf									// error buffer
		);

	if (handle== NULL)
	{
		// unable to open the adapter.
		return;
	}

	// tcp filter
	const char* filter = "tcp";
	struct bpf_program fcode;
	const bpf_u_int32 netmask = 0xffffffff;

	if (pcap_compile(handle, &fcode, filter, 1, netmask)< 0)
	{
		// error compiling filter
		return;
	}

	if (pcap_setfilter(handle, &fcode)< 0)
	{
		// error setting the filter
		return;
	}

	m_handle = handle;
}

void PacketCapturer::handle_close()
{
	pcap_t* handle = static_cast<pcap_t*>(m_handle);
	pcap_close(handle);
	m_handle = NULL;
}

int PacketCapturer::capture()
{
	if (m_handle== NULL) return -1;

	pcap_t* handle = static_cast<pcap_t*>(m_handle);
	struct pcap_pkthdr* header;
	const u_char* pkt_data;

	int res = pcap_next_ex(handle, &header, &pkt_data);
	if (res <= 0) return -1;


	// filtering
	if (m_flag_no_data== false)
	{
		if (header->len == (sizeof(ether_header) + sizeof(ip_header) + sizeof(tcp_header)))
			return -1;
	}

	// network frame
	ether_header* eth_hdr = (ether_header*)(pkt_data);
	if (ntohs(eth_hdr->ether_type) != ETHERTYPE_IP) return -1;

	std::vector<byte>& macAddr = getHostMacAddr();

	const bool my_recv = memcmp(eth_hdr->ether_dhost, &macAddr[0], 6)== 0;
	const bool my_send = memcmp(eth_hdr->ether_shost, &macAddr[0], 6)== 0;

	const bool isTestOkey = (m_flag_send && my_send) || (m_flag_recv && my_recv);
	if (isTestOkey== false) return -1;

	ip_header* ip_hdr = (ip_header*)(pkt_data + sizeof(ether_header));

	bool pass = true;
	for (auto itr = begin(m_filter_ip); itr != end(m_filter_ip); ++itr) {
		pass = (ip_hdr->ip_src == *itr || ip_hdr->ip_dst == *itr);
		if (pass== false) break;
	}
	if (pass== false) return -1;

	tcp_header* tcp_hdr = (tcp_header*)(pkt_data + sizeof(ether_header) + sizeof(ip_header));

	pass = true;
	for (auto itr = begin(m_filter_port); itr != end(m_filter_port); ++itr) {
		pass = (ntohs(tcp_hdr->th_sport)== *itr || ntohs(tcp_hdr->th_dport)== *itr);
		if (pass== false) break;
	}
	if (pass== false) return -1;
	// filtering

	pkt_info pkt;
	pkt.length = header->len;
	pkt.timestamp.resize(16);
	time_t local_tv_sec = header->ts.tv_sec;
	struct tm ltime;
	localtime_s(&ltime, &local_tv_sec);
	strftime(&pkt.timestamp[0], pkt.timestamp.size(), "%H:%M:%S", &ltime);
	pkt.raw_data.resize(header->len);
	pkt.raw_data.assign(&pkt_data[0], &pkt_data[header->len]);
	
	m_packets.push_back(pkt);

	return m_packets.size()- 1;
}

uint32 PacketCapturer::getNumPackets() const
{
	return m_packets.size();
}

void PacketCapturer::clearPackets()
{
	m_packets.clear();
}

uint32 PacketCapturer::getLength( uint32 index /*= LAST_HANDLE*/ )
{
	if (index == LAST_HANDLE)
		return m_packets.back().length;
	else
	{
		assert (0<= index && index< m_packets.size());
		return m_packets[index].length;
	}
}

const std::string& PacketCapturer::getTimeStamp( uint32 index /*= LAST_HANDLE*/ )
{
	if (index == LAST_HANDLE)
		return m_packets.back().timestamp;
	else
	{
		assert (0<= index && index< m_packets.size());
		return m_packets[index].timestamp;
	}
}

const std::string& PacketCapturer::getRawData( uint32 index /*= LAST_HANDLE*/ )
{
	if (index == LAST_HANDLE)
		return m_packets.back().raw_data;
	else
	{
		assert (0<= index && index< m_packets.size());
		return m_packets[index].raw_data;
	}
}

byte* PacketCapturer::getEtherHeader( uint32 index /*= LAST_HANDLE*/ )
{
	const char* ptr = &getRawData(index)[0];
	return (byte*)ptr;
}

byte* PacketCapturer::getIPHeader( uint32 index /*= LAST_HANDLE*/ )
{
	const char* ptr = &getRawData(index)[0];
	return (byte*)ptr + sizeof(ether_header);
}

byte* PacketCapturer::getTCPHeader( uint32 index /*= LAST_HANDLE*/ )
{
	const char* ptr = &getRawData(index)[0];
	return (byte*)ptr + sizeof(ether_header) + sizeof(ip_header);
}

byte* PacketCapturer::getDataPtr( uint32 index /*= LAST_HANDLE*/ )
{
	const char* ptr = &getRawData(index)[0];
	return (byte*)ptr + sizeof(ether_header) + sizeof(ip_header) + sizeof(tcp_header);	
}

uint32 PacketCapturer::getSourceIpAddr( uint32 index /*= LAST_HANDLE*/ )
{
	ip_header* iphdr = reinterpret_cast<ip_header*>(getIPHeader(index));
	return iphdr->ip_src;	
}

uint16 PacketCapturer::getSourcePort( uint32 index /*= LAST_HANDLE*/ )
{
	tcp_header* tcphdr = reinterpret_cast<tcp_header*>(getTCPHeader(index));
	return ntohs(tcphdr->th_sport);
}

uint32 PacketCapturer::getDestinationIpAddr( uint32 index /*= LAST_HANDLE*/ )
{
	ip_header* iphdr = reinterpret_cast<ip_header*>(getIPHeader(index));
	return iphdr->ip_dst;
}

uint16 PacketCapturer::getDestinationPort( uint32 index /*= LAST_HANDLE*/ )
{
	tcp_header* tcphdr = reinterpret_cast<tcp_header*>(getTCPHeader(index));
	return ntohs(tcphdr->th_dport);
}

void PacketCapturer::setTraceAddr( const char* szIpAddr, uint32 port )
{
	m_filter_ip.clear();
	m_filter_port.clear();
	
	if (szIpAddr)
		m_filter_ip.push_back(inet_addr(szIpAddr));

	if (port != 0)
		m_filter_port.push_back(port);
}
