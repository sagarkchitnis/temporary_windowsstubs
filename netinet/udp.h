#pragma once
/*
  2  * INET         An implementation of the TCP/IP protocol suite for the LINUX
  3  *              operating system.  INET is implemented using the  BSD Socket
  4  *              interface as the means of communication with the user level.
  5  *
  6  *              Definitions for the UDP protocol.
  7  *
  8  * Version:     @(#)udp.h       1.0.2   04/28/93
  9  *
  10  * Author:      Fred N. van Kempen, <waltje@uWalt.NL.Mugnet.ORG>
  11  *
  12  *              This program is free software; you can redistribute it and/or
  13  *              modify it under the terms of the GNU General Public License
  14  *              as published by the Free Software Foundation; either version
  15  *              2 of the License, or (at your option) any later version.
  16  */

#include <sys/wintypes.h>
//#ifdef __FAVOR_BSD

struct udphdr {
	u_int16_t uh_sport;  /* source port */
	u_int16_t uh_dport;  /* destination port */
	u_int16_t uh_ulen;   /* udp length */
	union {
		u_int16_t uh_sum;    /* udp checksum */
		u_int16_t check;
	};
};

//#else

//struct udphdr {
//	u_int16_t source;
//	u_int16_t dest;
//	u_int16_t len;
//	u_int16_t check;
//};

//#endif

 /* UDP socket options */
 #define UDP_CORK        1       /* Never send partially complete segments */
 #define UDP_ENCAP       100     /* Set the socket to accept encapsulated packets */
 #define UDP_NO_CHECK6_TX 101    /* Disable sending checksum for UDP6X */
 #define UDP_NO_CHECK6_RX 102    /* Disable accpeting checksum for UDP6 */

 /* UDP encapsulation types */
 #define UDP_ENCAP_ESPINUDP_NON_IKE      1 /* draft-ietf-ipsec-nat-t-ike-00/01 */
 #define UDP_ENCAP_ESPINUDP      2 /* draft-ietf-ipsec-udp-encaps-06 */
 #define UDP_ENCAP_L2TPINUDP     3 /* rfc2661 */
 #define UDP_ENCAP_GTP0          4 /* GSM TS 09.60 */
 #define UDP_ENCAP_GTP1U         5 /* 3GPP TS 29.060 */

