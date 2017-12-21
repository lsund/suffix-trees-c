#include "util.h"

void sstring(char *dst, const int i, const int n, const char *src)
{
    char tmp[n + 1];
    memcpy(tmp, &src[i], n);
    tmp[n] = '\0';
    sprintf(dst, "%s", tmp);
}

