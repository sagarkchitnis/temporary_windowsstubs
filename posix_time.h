#ifndef __POSIX_TIME_H__
#define __POSIX_TIME_H__

#include <ctime>
#include <winsock2.h>

char *strptime(const char *s, const char *format, struct tm *tm);
time_t timegm(struct tm *tm);
struct tm *gmtime_r(const time_t *timep, struct tm *result);

#endif // __POSIX_TIME_H__
