#pragma once
#include <sys/wintypes.h>
typedef int socklen_t;
#define MSG_DONTWAIT    0x40 
#define AF_LOCAL        1       /* POSIX name for AF_UNIX       */
#define AF_INET         2       /* Internet IP Protocol         */

#ifndef WIN_IOVEC
#define WIN_IOVEC
struct iovec {                    /* Scatter/gather array items */
	void  *iov_base;              /* Starting address */
	size_t iov_len;               /* Number of bytes to transfer */
};
#endif /* WIN_IOVEC */

struct msghdr {
	void         *msg_name;       /* optional address */
	socklen_t     msg_namelen;    /* size of address */
	struct iovec *msg_iov;        /* scatter/gather array */
	size_t        msg_iovlen;     /* # elements in msg_iov */
	void         *msg_control;    /* ancillary data, see below */
	size_t        msg_controllen; /* ancillary data buffer len */
	int           msg_flags;      /* flags on received message */
};

/* Socket configuration controls. */
#define SIOCGIFNAME     0x8910          /* get iface name               */
#define SIOCSIFLINK     0x8911          /* set iface channel            */
#define SIOCGIFCONF     0x8912          /* get iface list               */
#define SIOCGIFFLAGS    0x8913          /* get flags                    */
#define SIOCSIFFLAGS    0x8914          /* set flags                    */
#define SIOCGIFADDR     0x8915          /* get PA address               */
#define SIOCSIFADDR     0x8916          /* set PA address               */
#define SIOCGIFDSTADDR  0x8917          /* get remote PA address        */
#define SIOCSIFDSTADDR  0x8918          /* set remote PA address        */
#define SIOCGIFBRDADDR  0x8919          /* get broadcast PA address     */
#define SIOCSIFBRDADDR  0x891a          /* set broadcast PA address     */
#define SIOCGIFNETMASK  0x891b          /* get network PA mask          */
#define SIOCSIFNETMASK  0x891c          /* set network PA mask          */
#define SIOCGIFMETRIC   0x891d          /* get metric                   */
#define SIOCSIFMETRIC   0x891e          /* set metric                   */
#define SIOCGIFMEM      0x891f          /* get memory address (BSD)     */
#define SIOCSIFMEM      0x8920          /* set memory address (BSD)     */
#define SIOCGIFMTU      0x8921          /* get MTU size                 */
#define SIOCSIFMTU      0x8922          /* set MTU size                 */
#define SIOCSIFNAME     0x8923          /* set interface name */
#define SIOCSIFHWADDR   0x8924          /* set hardware address         */
#define SIOCGIFENCAP    0x8925          /* get/set encapsulations       */
#define SIOCSIFENCAP    0x8926
#define SIOCGIFHWADDR   0x8927          /* Get hardware address         */
#define SIOCGIFSLAVE    0x8929          /* Driver slaving support       */
#define SIOCSIFSLAVE    0x8930
#define SIOCADDMULTI    0x8931          /* Multicast address lists      */
#define SIOCDELMULTI    0x8932
#define SIOCGIFINDEX    0x8933          /* name -> if_index mapping     */
#define SIOGIFINDEX     SIOCGIFINDEX    /* misprint compatibility :-)   */
#define SIOCSIFPFLAGS   0x8934          /* set/get extended flags set   */
#define SIOCGIFPFLAGS   0x8935
#define SIOCDIFADDR     0x8936          /* delete PA address            */
#define SIOCSIFHWBROADCAST      0x8937  /* set hardware broadcast addr  */
#define SIOCGIFCOUNT    0x8938          /* get number of devices */
