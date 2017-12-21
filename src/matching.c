#include "matching.h"

Matching matching_empty()
{
    Matching ret;
    ret.match      = NULL;
    ret.rest_left  = NULL;
    ret.rest_right = NULL;
    return ret;
}

MatchType match_type(const Matching match)
{
    if (!match.match) {
        return NONE;
    } else if (!match.rest_left && !match.rest_right) {
        return EXACT;
    } else if (!match.rest_left) {
        return PARTIAL_LEFT;
    } else {
        return PARTIAL_RIGHT;
    }
}


Matching match(const char *left, const char *right)
{

    Matching ret;
    unsigned long i, left_len, right_len, max_len;

    i = 0;
    left_len= strlen(left);
    right_len = strlen(right);
    max_len = right_len > left_len ? right_len : left_len;

    while (i < max_len && right[i] == left[i]) {
        i++;
    }

    if (i > 0) {
        if (i == max_len) {
            // the two strings were identical
            ret.rest_right = NULL;
            ret.rest_left = NULL;
        } else if (i == right_len) {
            // The whole pattern got matched
            ret.rest_right = NULL;
            char *rest_left = malloc(sizeof(char) * 128);
            sstring(left, i, strlen(left) - i, rest_left);
        } else if (i == left_len) {
            // The whole input got matched
            ret.rest_left = NULL;
            char *rest_right = malloc(sizeof(char) * 128);
            sstring(right, i, strlen(right) - i, rest_right);
        }

        char *match = malloc(sizeof(char) * 128);
        sstring(right, 0, i, match);
        ret.match = match;

    } else {
        ret.match      = NULL;
        ret.rest_left  = NULL;
        ret.rest_right = NULL;
    }
    return ret;
}


