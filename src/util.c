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

static void swap(char *a, char *b)
{
    char t = *a;
    *a = *b;
    *b = t;
}

static void permute(char *s, int i, int n, char *t)
{
   if (i == (n - 1)) {
       strcat(t, s);

   } else {

     for (int j = i; j < n; j++) {
       swap((s + i), (s + j));
       permute(s, i + 1, n, t);
       swap((s + i), (s + j));
     }

   }
}


void all_permutations(char *s, char *t)
{
    permute(s, 0, strlen(s), t);
}


void nth_permutation(int i, char *s, char *t)
{
    int len, size;
    char tmp[STRING_MAX_LEN];

    len = strlen(s);
    size = sizeof(char) * len;

    tmp[0] = '\0';
    all_permutations(s, tmp);
    strncpy(t, tmp + (i * size), size);
    t[len] = '\0';
}

