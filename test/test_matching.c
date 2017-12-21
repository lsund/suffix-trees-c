#include "test.h"
#include "matching.h"

char *utest_matching_match()
{
    Matching m0 = match("xest", "test");
    mu_assert("No match", match_type(m0) == NONE);

    Matching m = match("test", "xest");
    mu_assert("No match", match_type(m) == NONE);

    Matching m2 = match("xest", "xest");
    mu_assert("Exact match", strcmp(m2.match, "xest") == 0);
    mu_assert("Exact match", m2.rest_left == NULL);
    mu_assert("Exact match", m2.rest_right == NULL);
    mu_assert("Exact match", match_type(m2) == EXACT);

    Matching m3 = match("xest", "xester");
    mu_assert("Partial match left", strcmp(m3.match, "xest") == 0);
    mu_assert("Partial match left", m3.rest_left == NULL);
    mu_assert("Partial match left", strcmp(m3.rest_right, "er") == 0);
    mu_assert("Partial match left", match_type(m3) == PARTIAL_LEFT);

    Matching m4 = match("xester", "xest");
    mu_assert("Partial match left", strcmp(m4.match, "xest") == 0);
    mu_assert("Partial match left", m4.rest_right == NULL);
    mu_assert("Partial match left", strcmp(m4.rest_left, "er") == 0);
    mu_assert("Partial match left", match_type(m4) == PARTIAL_RIGHT);
    return NULL;
}

char *test_matching()
{
    mu_run_utest(utest_matching_match);
    return NULL;
}
