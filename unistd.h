#pragma once

#include <io.h>
#include <process.h>

#define STDOUT_FILENO   1

typedef unsigned int useconds_t;

#ifdef __cplusplus
extern "C" {
#endif

unsigned int sleep(unsigned int seconds);
int usleep(useconds_t usec);

#ifdef __cplusplus
}
#endif
