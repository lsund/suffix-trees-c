#include "util.h"

void sstring(const char *s, const int i, const int n, char *buf)
{
    char subbuff[n + 1];
    memcpy(subbuff, &s[i], n);
    subbuff[n] = '\0';
    sprintf(buf, "%s", subbuff);
}

