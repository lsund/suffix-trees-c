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


Matching match(Label left, Label right)
{

    Matching ret;
    int size, min_len, rlen, llen;
    char lc, rc;

    size    = 0;
    llen    = left->j - left->i;
    rlen    = right->j - right->i;
    min_len = rlen > llen ? llen : rlen;

    while  (size < min_len) {

        rc = label_char_at(right, size);
        lc = label_char_at(left, size);

        if (rc != lc) {
            break;
        } else {
            size++;
        }

    }

    ret.size  = size;
    ret.left  = llen - size;
    ret.right = rlen - size;


    return ret;
}
