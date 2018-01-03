#include "matching.h"

Matching matching_empty()
{
    Matching ret;
    ret.size  = 0;
    ret.left  = 0;
    ret.right = 0;
    return ret;
}

MatchType match_type(const Matching match)
{
    if (match.size) {
        if (!match.left && !match.right) {
            return EXACT;
        } else {
            return match.left ? PARTIAL_LEFT : PARTIAL_RIGHT;
        }
    } else {
        if (match.left && match.right) {
            return NONE;
        } else {
            return match.left ? PARTIAL_LEFT : PARTIAL_RIGHT;
        }
    }
}


Matching match(char *left, char *right)
{

    Matching ret;
    int size, max_len, rlen, llen;

    size = 0;
    llen= strlen(left);
    rlen = strlen(right);
    max_len = rlen > llen ? rlen : llen;

    while (size < max_len && right[size] == left[size]) {
        size++;
    }

    ret.size  = size;
    ret.left  = llen - size;
    ret.right = rlen - size;


    return ret;
}
