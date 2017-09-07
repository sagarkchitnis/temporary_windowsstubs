#pragma once
/*
*	Types and definitions for AF_INET6
*	Linux INET6 implementation
*
*	Authors:
*	Pedro Roque		<roque@di.fc.ul.pt>
*
*	Sources:
*	IPv6 Program Interfaces for BSD Systems
*      <draft-ietf-ipngwg-bsd-api-05.txt>
*
*	Advanced Sockets API for IPv6
*	<draft-stevens-advanced-api-00.txt>
*
*	This program is free software; you can redistribute it and/or
*      modify it under the terms of the GNU General Public License
*      as published by the Free Software Foundation; either version
*      2 of the License, or (at your option) any later version.
*/


/*
*	IPv6 address structure
*/
#include <sys/wintypes.h>

//#if __UAPI_DEF_IN6_ADDR
struct linux_in6_addr {
    union {
        u_char  Byte[16];
        u_short Word[8];
        u_int   Dword[4];
    } u;

#define s6_addr16		u.Word
#define s6_addr32		u.Dword
};
//#endif /* __UAPI_DEF_IN6_ADDR */

#if __UAPI_DEF_SOCKADDR_IN6
struct sockaddr_in6 {
	unsigned short int	sin6_family;    /* AF_INET6 */
	__be16			sin6_port;      /* Transport layer port # */
	__be32			sin6_flowinfo;  /* IPv6 flow information */
	struct linux_in6_addr		sin6_addr;      /* IPv6 address */
	__u32			sin6_scope_id;  /* scope id (new in RFC2553) */
};
#endif /* __UAPI_DEF_SOCKADDR_IN6 */

#if __UAPI_DEF_IPV6_MREQ
struct ipv6_mreq {
	/* IPv6 multicast address of group */
	struct linux_in6_addr ipv6mr_multiaddr;

	/* local IPv6 address of interface */
	int		ipv6mr_ifindex;
};
#endif /* __UAPI_DEF_IVP6_MREQ */

#define ipv6mr_acaddr	ipv6mr_multiaddr

struct in6_flowlabel_req {
	struct linux_in6_addr	flr_dst;
	__be32	flr_label;
	__u8	flr_action;
	__u8	flr_share;
	__u16	flr_flags;
	__u16 	flr_expires;
	__u16	flr_linger;
	__u32	__flr_pad;
	/* Options in format of IPV6_PKTOPTIONS */
};
