#pragma once

typedef unsigned __int8		uint8;
typedef unsigned __int16	uint16;
typedef unsigned __int32	uint32;

typedef uint8	byte;
typedef uint16	half;
typedef uint32	uint;

//< ethernet header define
#define ETHER_ADDR_LEN		6

/*  Ethernet_II header */

typedef struct ether_header {
	unsigned __int8  ether_dhost[ETHER_ADDR_LEN];
	unsigned __int8  ether_shost[ETHER_ADDR_LEN];
	unsigned __int16 ether_type;
} ether_header;

#define ETHERTYPE_PUP         0x0200  /* PUP protocol */
#define ETHERTYPE_IP          0x0800  /* IP protocol */
#define ETHERTYPE_ARP         0x0806  /* Addr. resolution protocol */
#define ETHERTYPE_REVARP      0x8035  /* reverse Addr. resolution protocol */

/* IPv4 header : RFC 791 */
typedef struct ip_header
{
	unsigned __int8  ip_vhl;              /* version << 4 | header length >> 2 */
	unsigned __int8  ip_tos;              /* Type of service */
	unsigned __int16 ip_len;              /* Total length */
	unsigned __int16 ip_id;               /* Identification */
	unsigned __int16 ip_off;              /* Flags (3 bits) + Fragment offset (13 bits) */
#define IP_RF 0x8000                          /* reserved fragment flag */
#define IP_DF 0x4000                          /* dont fragment flag */
#define IP_MF 0x2000                          /* more fragments flag */
#define IP_OFFMASK 0x1fff                     /* mask for fragmenting bits */
	unsigned __int8  ip_ttl;              /* Time to live */
	unsigned __int8  ip_p;                /* Protocol */
	unsigned __int16 ip_sum;              /* Header checksum */
	unsigned __int32 ip_src;              /* Source address */
	unsigned __int32 ip_dst;              /* Destination address */
	//unsigned __int32 op_pad;              /* Option + Padding */
} ip_header;


#define IP_HL(ip)             (((ip)->ip_vhl) & 0x0f)
#define IP_V(ip)              (((ip)->ip_vhl) >> 4)

/* TCP Header : RFC 793 */
typedef struct tcp_header
{
	unsigned __int16 th_sport;      /* Source port */
	unsigned __int16 th_dport;      /* Destination port */  
	unsigned __int32 th_seq;        /* Sequence number */ 
	unsigned __int32 th_ack;        /* Acknowledgement number */
	unsigned __int8  th_offx2;      /* Data offset + Reserved */
#define TH_OFF(th)     (((th)->th_offx2 & 0xf0) >> 4)
	unsigned __int8  th_flags;      /* flags */
#define TH_FIN  0x01
#define TH_SYN  0x02
#define TH_RST  0x04
#define TH_PUSH 0x08
#define TH_ACK  0x10
#define TH_URG  0x20
#define TH_ECE  0x40                    /* ECN Echo */
#define TH_CWR  0x80                    /* ECN Cwnd Reduced */
#define TH_FLAGS (TH_FIN | TH_SYN | TH_RST | TH_ACK | TH_URG | TH_ECE | TH_CWR)
	unsigned __int16 th_win;        /* Window size */ 
	unsigned __int16 th_sum;        /* Checksum */
	unsigned __int16 th_urp;        /* Urgent pointer */
	//unsigned __int32 th_oppad;      /* Option + Padding */
} tcp_header;



typedef struct address
{
	address(uint32 a) : addr(a) {}
	address(byte b1, byte b2, byte b3, byte b4)
		: byte1(b1), byte2(b2), byte3(b3), byte4(b4) {}
	union 
	{
		struct 
		{
			uint8 byte1;
			uint8 byte2;
			uint8 byte3;
			uint8 byte4;
		};
		uint32 addr;
	};
} address; 