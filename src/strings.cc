#define WIN32_LEAN_AND_MEAN

#include <strings.h>
#include <windows.h>

int ffs(int i) {
    ULONG index, mask = (ULONG)i;
    UCHAR isNonzero = _BitScanForward(&index, mask);
    if (isNonzero)
        return index + 1;
    else
        return 0;
}

int strncasecmp(const char *s1, const char *s2, size_t n) {
    return _strnicmp(s1, s2, n);
}
