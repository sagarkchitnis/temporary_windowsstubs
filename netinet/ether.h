#pragma once

#include <net/ethernet.h>

struct ether_addr *ether_aton(const char *asc);
char *ether_ntoa(const struct ether_addr *addr);
