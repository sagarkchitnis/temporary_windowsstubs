#ifndef __TASKUTIL_H__
#define __TASKUTIL_H__

#include <string>

bool WindowsTaskExecute(std::string execpath, std::string *pOutput = nullptr, bool bWait = true);
FILE *popen(const char *command, const char *type);
int pclose(FILE *stream);
int CountProcessThreads(unsigned long dwOwnerPID);
unsigned long GetNumberOfCPUs();
int getloadavg(double loadavg[], int nelem);

#endif // __TASKUTIL_H__
