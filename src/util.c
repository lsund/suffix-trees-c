#include "util.h"


int runtime_error(const char *msg)
{
    fprintf(stderr, "Error: %s\n", msg);
    exit(1);
    return 1;
}


void sstring(char *dst, const int i, const int n, const char *src)
{
    *dst = '\0';
    char tmp[n + 1];
    memcpy(tmp, &src[i], n);
    tmp[n] = '\0';
    sprintf(dst, "%s", tmp);
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


static void permute(char *t, char *s, int i, int n)
{
   if (i == (n - 1)) {
       strcat(t, s);

   } else {

     for (int j = i; j < n; j++) {
       swap((s + i), (s + j));
       permute(t, s, i + 1, n);
       swap((s + i), (s + j));
     }

   }
}


void all_permutations(char *t, char *s)
{
    permute(t, s, 0, strlen(s));
}


void nth_permutation(char *t, int i, char *s)
{
    int len, size;
    char tmp[STRING_MAX_LEN];

    tmp[0] = '\0';
    len = strlen(s);
    size = sizeof(char) * len;

    all_permutations(tmp, s);
    strncpy(t, tmp + (i * size), size);
    t[len] = '\0';
}


int permutation_inverse_number(int i, int n)
{
    int size;
    char all[STRING_MAX_LEN];
    char perm_seq[STRING_MAX_LEN];
    char cand[STRING_MAX_LEN];
    char res[STRING_MAX_LEN];
    char permuted[STRING_MAX_LEN];
    char s[STRING_MAX_LEN];

    size = sizeof(char) * n;
    all[0]      = '\0';
    cand[0]     = '\0';
    cand[n]     = 0;
    res[0]      = '\0';
    permuted[0] = 0;

    nat_sequence(s, n);
    all_permutations(all, s);
    strncpy(perm_seq, all + (i * size), size);
    perm_seq[n] = 0;

    for (int l = 0; l < n; l++) {
        int d = char_to_int(perm_seq[l]);
        permuted[l] = s[d];
    }
    permuted[n] = 0;

    for (int k = 0; k < n * factorial(size); k += size) {

        strncpy(cand, all + k, size);
        res[0] = 0;
        res[n] = 0;

        for (int l = 0; l < n; l++) {
            int d = char_to_int(cand[l]);
            res[l] = permuted[d];
        }

        if (strcmp(res, s) == 0) {
            return k / n;
        }
    }
    return -1;
}


void nat_sequence(char *t, int i)
{
    if (i > 9) {
        runtime_error("nat_sequence: cannot create sequence larger than 10");
        return;
    }
    t[0] = '\0';
    char tmp[STRING_MAX_LEN];
    for (int j = 0; j < i; j++) {
        tmp[0] = '\0';
        sprintf(tmp, "%d", j);
        tmp[1] = '\0';
        strcat(t, tmp);
    }
}


int factorial(const int i)
{
    if (i == 0) {
        return 1;
    } else {
        return i * factorial(i - 1);
    }
}
