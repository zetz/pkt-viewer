#pragma once

#include "EtherDefine.h"

#include <string>
#include <vector>

class PacketCapturer
{
	// singleton instance
	PacketCapturer();
	PacketCapturer(const PacketCapturer& rhs) {};
public:
	~PacketCapturer(void);

	static PacketCapturer& instance();
	static PacketCapturer* pointer();

	bool		initialize();	// get the host info (ex: dev, ip, ...)
	void		finalize();

	// host info
	uint32		getNumDevice() const;
	const std::string& getDeviceDesc(uint32 index) const;
	void		setDeviceIndex(uint32 index);
	uint32		getDeviceIndex() const;

	// selected device info
	uint32		getHostIpAddr();
	std::vector<uint8>& getHostMacAddr();

	enum {
		LAST_HANDLE = -1,
	};

	void		handle_open();
	void		handle_close();

	int			capture();
	uint32		getNumPackets() const;		// saved packet count.
	void		clearPackets();

	uint32		getLength(uint32 index = LAST_HANDLE);	
	const std::string& getTimeStamp(uint32 index = LAST_HANDLE);
	const std::string& getRawData(uint32 index = LAST_HANDLE);

	byte*		getEtherHeader(uint32 index = LAST_HANDLE);
	byte*		getIPHeader(uint32 index = LAST_HANDLE);
	byte*		getTCPHeader(uint32 index = LAST_HANDLE);
	byte*		getDataPtr(uint32 index = LAST_HANDLE);
	
	uint32		getSourceIpAddr(uint32 index = LAST_HANDLE);
	uint16		getSourcePort(uint32 index = LAST_HANDLE);
	uint32		getDestinationIpAddr(uint32 index = LAST_HANDLE);	
	uint16		getDestinationPort(uint32 index = LAST_HANDLE);


	// filter
	void		setTraceAddr(const char* szIpAddr, uint32 port);

	void		setSend(bool v) { m_flag_send = v; }
	bool		getSend() const { return m_flag_send; }

	void		setRecv(bool v) { m_flag_recv = v; }
	bool		getRecv() const { return m_flag_recv; }

	void		setNoDataSkip(bool v) { m_flag_no_data = v; }
	bool		getNoDataSkip() const { return m_flag_no_data; }

private:

	// device
	struct dev_info {
		std::string name;
		std::string desc;
		std::vector<uint32> ip_list;
		std::vector<uint8> mac_addr;
	};

	std::vector<dev_info>	m_devices;
	uint32					m_selcted_device;

	// packets
	void*				m_handle;
	struct pkt_info {
		uint32 length;
		std::string timestamp;
		std::string raw_data;
	};

	std::vector<pkt_info>	m_packets;

	// trace target
	std::vector<uint32>		m_filter_ip;
	std::vector<uint16>		m_filter_port;

	bool					m_flag_recv;
	bool					m_flag_send;
	bool					m_flag_no_data;		// skip the header only packet. (don't have a user data)
};

