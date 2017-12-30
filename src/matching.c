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
    if (!match.success) {
        return NONE;
    } else if (match.success && !match.rest_left && !match.rest_right) {
        return EXACT;
    } else if (match.success && !match.rest_left) {
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

            ret.rest_right = NULL;
            ret.rest_left = NULL;

        } else if (i == right_len) {

            char *rest_left = malloc(sizeof(char) * 128);
            sstring(rest_left, i, left_len, left);

            ret.rest_right = NULL;
            ret.rest_left = rest_left;

        } else if (i == left_len) {
            char *rest_right = malloc(sizeof(char) * 128);
            sstring(rest_right, i, right_len, right);

            ret.rest_left = NULL;
            ret.rest_right = rest_right;
        }

        char *match = malloc(sizeof(char) * 128);
        sstring(match, 0, i, left);
        ret.match = match;
        ret.success = 1;

    } else {

        ret.success = right_len == 0;
        ret.rest_right = NULL;
        ret.match      = NULL;
        if (left_len == 0) {
            ret.rest_left  = NULL;
        } else {
            ret.rest_left = left;
        }

    }
    return ret;
}


