#pragma once
#define WIN32_LEAN_AND_MEAN
#include<windows.h>
#include <stdlib.h>

#include <string> // TODO: JW-522 Refactor
#include <sstream>

int getloadavg(double loadavg[], int nelem);;

#define CLOCK_REALTIME                  0
#define CLOCK_MONOTONIC                 1

typedef unsigned int            uint;
typedef unsigned long           ulong;
typedef ptrdiff_t ssize_t;
typedef int clockid_t;
char *ctime_r(time_t*, char[]);

int clock_gettime(clockid_t clk_id, struct timespec *tv);
int clock_getres(clockid_t clk_id, struct timespec *res);

char *windows_if_indextoname(unsigned int ifindex, char *ifname);
char *gettempdirectory();
DWORD getppid();
void WindowsCloseTaskFiles();

#define PACK( ___somestructure___ ) __pragma( pack(push, 1) ) ___somestructure___ __pragma( pack(pop) )
#define strtok_r strtok_s



void bzero(void *to, int count);
typedef unsigned long   __kernel_ulong_t;
struct rlimit {
	         __kernel_ulong_t        rlim_cur;
	         __kernel_ulong_t        rlim_max;
};
#ifndef RLIMIT_NOFILE
# define RLIMIT_NOFILE          7       /* max number of open files */
#endif

int getrlimit(int resource, struct rlimit *rlp);

int setrlimit(int resource, const struct rlimit *rlp);

#define strncasecmp  _strnicmp
#define strcasecmp  _stricmp

std::string GetFormattedWindowsErrorMsg(); // TODO: JW-522 Refactor

void sync(void);
std::string GetWindowsVersionString();
