#pragma once

#include <unistd.h>

#define TIOCGWINSZ      1

struct winsize {
    unsigned short ws_row;	/* rows, in characters */
    unsigned short ws_col;	/* columns, in characters */
};

#ifdef __cplusplus
extern "C" {
#endif

int ioctl(int fd, unsigned long request, ...);

#ifdef __cplusplus
}
#endif
