#define WIN32_LEAN_AND_MEAN

#include <unistd.h>
#include <windows.h>

unsigned int sleep(unsigned int seconds) { 
    ::Sleep(1000 * seconds);
    return 0;
}

int usleep(useconds_t usec) {
    ::Sleep((usec + 999U) / 1000U); // divide by 1000 and round up
    return 0;
}
