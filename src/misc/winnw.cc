#include "winutils.h"
#include "winnw.h"
#include "net/ethernet.h"
#include <intrin.h> 
#include <Iphlpapi.h>

static inline int xdigit(char c) {
    unsigned d;
    d = (unsigned)(c - '0');
    if (d < 10) return (int)d;
    d = (unsigned)(c - 'a');
    if (d < 6) return (int)(10 + d);
    d = (unsigned)(c - 'A');
    if (d < 6) return (int)(10 + d);
    return -1;
}

unsigned int  windows_if_nametoindex(char const* name) {
    return ::if_nametoindex(name);
}
void windows_if_freenameindex(struct if_nameindex* nameindex) {
    ::free(nameindex);
}
struct if_nameindex* windows_if_nameindex(void) {
    // windows-temp assert(0);
    return 0;
}

char* windows_if_indextoname(unsigned int ifindex, char* ifname) {
    return ::if_indextoname(ifindex, ifname);
}

struct ether_addr* ether_aton_r(const char *asc, struct ether_addr * addr) {
    int i, val0, val1;
    for (i = 0; i < ETHER_ADDR_LEN; ++i) {
        val0 = xdigit(*asc);
        asc++;
        if (val0 < 0)
            return NULL;

        val1 = xdigit(*asc);
        asc++;
        if (val1 < 0)
            return NULL;

        addr->ether_addr_octet[i] = (u_int8_t)((val0 << 4) + val1);

        if (i < ETHER_ADDR_LEN - 1) {
            if (*asc != ':')
                return NULL;
            asc++;
        }
    }
    if (*asc != '\0')
        return NULL;
    return addr;
}

struct ether_addr* ether_aton(const char* asc) {
    static struct ether_addr addr;
    return ether_aton_r(asc, &addr);
}

u_int32_t custom_htonl(u_int32_t x) {
    u_char* s = (u_char*)&x;
    return (u_int32_t)(s[0] << 24 | s[1] << 16 | s[2] << 8 | s[3]);
}
