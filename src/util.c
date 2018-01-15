#include "util.h"

void sstring(char *dst, const int i, const int n, const char *src)
{
    *dst = '\0';
    char tmp[n + 1];
    memcpy(tmp, &src[i], n);
    tmp[n] = '\0';
    sprintf(dst, "%s", tmp);
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

void swap(char *a, char *b)
{
    char t = *a;
    *a = *b;
    *b = t;
}

void permute(char *a, int i, int n, char *dst)
{
   if (i == (n - 1)) {
       strcat(dst, a);

   } else {

     for (int j = i; j < n; j++) {
       swap((a + i), (a + j));
       permute(a, i + 1, n, dst);
       swap((a + i), (a + j));
     }

   }
}

