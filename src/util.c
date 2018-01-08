#include "util.h"

void sstring(char *dst, const int i, const int n, const char *src)
{
    *dst = '\0';
    char tmp[n + 1];
    memcpy(tmp, &src[i], n);
    tmp[n] = '\0';
    sprintf(dst, "%s", tmp);
}

void extend(char *s, char c)
{
    *(s + strlen(s)) = c;
}

int runtime_error(const char *msg)
{
    fprintf(stderr, "Error: %s\n", msg);
    exit(1);
    return -99;
}

int char_to_int(char c)
{
    return c - 48;
}

