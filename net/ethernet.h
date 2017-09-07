
#pragma once
#include "sys/wintypes.h"

#define PACK( __Declaration__ ) __pragma( pack(push, 1) ) __Declaration__ __pragma( pack(pop) )

#define ETH_ALEN   6
#define ETHERTYPE_VLAN (0x8100)

PACK(
struct ether_addr
{
	unsigned char ether_addr_octet[ETH_ALEN];
};
);