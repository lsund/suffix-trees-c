#include "matching.h"

Matching matching_empty()
{
    Matching ret;
    ret.match_both = 0;
    ret.unmatched_left = ret.unmatched_right = 0;
    return ret;
}

MatchType match_type(const Matching match)
{
    if (match.success) {
        if (!match.unmatched_left && !match.unmatched_right) {
            return EXACT;
        } else {
             return match.unmatched_left ? PARTIAL_LEFT : PARTIAL_RIGHT;
        }
    }
    return NONE;
}


Matching match(char *left, char *right)
{

    Matching ret;
    int match_both, max_len, right_len, left_len;

    match_both = 0;
    left_len= strlen(left);
    right_len = strlen(right);
    max_len = right_len > left_len ? right_len : left_len;

    while (match_both < max_len && right[match_both] == left[match_both]) {
        match_both++;
    }

    ret.success = match_both > 0 || left_len == 0 || right_len == 0;

    ret.unmatched_left = left_len - match_both;
    ret.unmatched_right = right_len - match_both;
    ret.match_both = match_both;

    return ret;
}

void matching_destroy(Matching m)
{
    //TODO
}
