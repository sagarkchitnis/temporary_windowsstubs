#include <windows.h>
#include <cstdio>
#include <tchar.h>
#include <iostream>
#include <string>
#include <cctype>
#include <algorithm>
#include <process.h>
#include <memory>
#include <tlhelp32.h>
#include <psapi.h>
#include <cassert>

FILE *popen(const char *command, const char *type) {
    return _popen(command, type);
}

int pclose(FILE *stream) {
    return _pclose(stream);
}

struct ProcessInfoDeleter {
    void operator()(PROCESS_INFORMATION* ppi) {
        if (ppi) {
            if (ppi->hProcess) {
                CloseHandle(ppi->hProcess);
            }
            if (ppi->hThread) {
                CloseHandle(ppi->hThread);
            }
            delete ppi;
        }
    }
};

bool WindowsTaskExecute(std::string execpath, std::string *pOutput, bool bWait) {
    STARTUPINFO si;
    SECURITY_ATTRIBUTES securityAttr;
    HANDLE inputPipe = INVALID_HANDLE_VALUE, outputPipe = INVALID_HANDLE_VALUE;
    bool retval = true;
    std::unique_ptr<PROCESS_INFORMATION,ProcessInfoDeleter>
        upi(new PROCESS_INFORMATION);

    // only for clarity purposes, ownership is not relinquished
    PROCESS_INFORMATION *ppi = upi.get();

    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    ZeroMemory(ppi, sizeof(PROCESS_INFORMATION));
    ZeroMemory(&securityAttr, sizeof(securityAttr));
    securityAttr.nLength = sizeof(securityAttr);
    securityAttr.bInheritHandle = TRUE;
    int len;
    int slength = (int)execpath.length() + 1;

    // CP_ACP instructs the API to use the currently set default Windows
    // ANSI codepage
    len = MultiByteToWideChar(CP_ACP, 0, execpath.c_str(), slength, 0, 0);

    auto ubuf = std::unique_ptr<wchar_t[]>{ new wchar_t[len] };
    wchar_t *pbuf = ubuf.get(); // only for clarity
    MultiByteToWideChar(CP_ACP, 0, execpath.c_str(), slength, pbuf, len);
    if (pOutput) {
        if (CreatePipe(&inputPipe, &outputPipe, &securityAttr, 0) != 0) {
            si.dwFlags = STARTF_USESTDHANDLES;
            si.hStdInput = NULL;
            si.hStdOutput = outputPipe;
            si.hStdError = outputPipe;
        } else {
            // Set it to null so that later the pipe related functionality
            // is skipped. Allow other functionality to execute.
            pOutput = nullptr;
        }
    }

    if (!CreateProcess(NULL, pbuf, NULL, NULL, TRUE, 0, NULL, NULL, &si, ppi)) {
        DWORD le = GetLastError();
        std::cout << "CreateProcess Failed. Error code:" << le << std::endl;
        retval = false;
    }
    
    if (bWait && retval && WaitForSingleObject(ppi->hProcess, INFINITE) == WAIT_FAILED) {
        DWORD le = GetLastError();
        std::cout << "WaitForSingleObject Failed. Error code:" << le << std::endl;
        retval = false;
    }

    if (outputPipe != INVALID_HANDLE_VALUE)
        CloseHandle(outputPipe);

    if (retval && pOutput) {
        const int BUFFER_SIZE = 200;
        DWORD nNumberOfBytesToRead = 0;
        do {
            char localbuf[BUFFER_SIZE + 1];
            if (::ReadFile(inputPipe, localbuf, BUFFER_SIZE, &nNumberOfBytesToRead, 0)) {
                if (nNumberOfBytesToRead == 0)
                    break;
                localbuf[nNumberOfBytesToRead] = '\0';
                *pOutput += localbuf;
         }

        } while (nNumberOfBytesToRead != 0);
    }

    if (inputPipe != INVALID_HANDLE_VALUE)
        CloseHandle(inputPipe);

    return retval;
}

//see https://msdn.microsoft.com/en-us/library/ms686852(v=VS.85).aspx

int CountProcessThreads(DWORD id) {
    HANDLE hThreadSnap = INVALID_HANDLE_VALUE;
    BOOL  retval = true;
    PROCESSENTRY32 pe32 = { 0 };
    int count = -1;
    pe32.dwSize = sizeof(PROCESSENTRY32);

    hThreadSnap = CreateToolhelp32Snapshot(TH32CS_SNAPALL, 0);

    if (hThreadSnap != INVALID_HANDLE_VALUE) {
        retval = Process32First(hThreadSnap, &pe32);
        do {
            if (pe32.th32ProcessID == id) {
                count = pe32.cntThreads; break;
            }
        } while (Process32Next(hThreadSnap, &pe32));

        CloseHandle(hThreadSnap);
    }
    return count;
}

void sync(void) {
    _flushall(); // does it call FlushFileBuffers internally for all files?
}

BOOL GetCurrentProcessMemoryInfo(uint32_t& virt, uint32_t& peakvirt, uint32_t& res) {
    virt = peakvirt = res = 0;
    PROCESS_MEMORY_COUNTERS_EX pmc;
    BOOL bRet = 0;
    if (bRet = GetProcessMemoryInfo(GetCurrentProcess(), (PROCESS_MEMORY_COUNTERS*)&pmc, sizeof(pmc))) {
        // return in KB, need to verify the mapping 
        // may need to convert back to non-kb.
        virt = pmc.PrivateUsage/1024;
        peakvirt = pmc.PeakWorkingSetSize/1024;
        res = pmc.WorkingSetSize/1024;
    }
    return bRet;
}

int getloadavg(double loadavg[], int nelem) {
    
    return 0;
   
}

// https://msdn.microsoft.com/en-us/library/windows/desktop/ms682499(v=vs.85).aspx