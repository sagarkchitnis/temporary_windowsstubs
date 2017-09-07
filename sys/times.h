#pragma once

#include <ctime>
#include <sys/time.h>

struct tms {
    clock_t tms_utime;  /* user time */
    clock_t tms_stime;  /* system time */
    clock_t tms_cutime; /* user time of children */
    clock_t tms_cstime; /* system time of children */
};

// Always returns 0.
clock_t times(struct tms *buf); 
