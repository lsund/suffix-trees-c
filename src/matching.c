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


Matching match(LabelPointer left, LabelPointer right)
{

    Matching ret;
    int size, max_len, rlen, llen;

    size    = 0;
    llen    = left->n - left->i;
    rlen    = right->n - right->i;
    max_len = rlen > llen ? rlen : llen;

    while  (size < max_len &&
            right->mark[right->i + size] == left->mark[left->i + size])
    {
        size++;
    }

    ret.size  = size;
    ret.left  = llen - size;
    ret.right = rlen - size;


    return ret;
}
