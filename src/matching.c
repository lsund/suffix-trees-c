#include "matching.h"

MatchType match_type(const Matching match)
{
    if (!match.match) {
        return NONE;
    } else if (!match.rest) {
        return EXACT;
    } else {
        return PARTIAL;
    }
}


Matching match(const char *a, const char *b)
{

    Matching ret;
    unsigned long i, a_len, b_len, max_len;

    i = 0;
    b_len = strlen(b);
    a_len= strlen(a);
    max_len = b_len > a_len ? b_len : a_len;

    while (i < max_len && b[i] == a[i]) {
        i++;
    }
    if (i > 0) {

        char *match = malloc(sizeof(char) * 128);
        sstring(b, 0, i, match);
        ret.match = match;

        if (i < max_len) {

            char *rest = malloc(sizeof(char) * 128);
            sstring(b, i, strlen(b) - i, rest);
            ret.rest  = rest;

        } else {
            ret.rest = NULL;
        }
    } else {
        ret.match = NULL;
        ret.rest  = NULL;
    }

    return ret;
}


