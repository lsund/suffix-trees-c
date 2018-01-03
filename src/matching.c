#include "matching.h"

Matching matching_empty()
{
    Matching ret;
    ret.size = 0;
    ret.left = ret.right = 0;
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
    int size, max_len, right_len, left_len;

    size = 0;
    left_len= strlen(left);
    right_len = strlen(right);
    max_len = right_len > left_len ? right_len : left_len;

    while (size < max_len && right[size] == left[size]) {
        size++;
    }

    ret.left = left_len - size;
    ret.right = right_len - size;
    ret.size = size;

    return ret;
}
