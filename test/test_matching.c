#include "test.h"
#include "matching.h"

char *utest_matching_match()
{
    Matching m0 = match("xest", "test");
    mu_assert("No match #1", match_type(m0) == NONE);

    Matching m = match("test", "xest");
    mu_assert("No match #2", match_type(m) == NONE);

    Matching m2 = match("xest", "xest");
    mu_assert("Exact match", strcmp(m2.match, "xest") == 0);
    mu_assert("Exact match", m2.rest_left == NULL);
    mu_assert("Exact match", m2.rest_right == NULL);
    mu_assert("Exact match", match_type(m2) == EXACT);

    Matching m3 = match("xest", "xester");
    mu_assert("Partial match left #1", strcmp(m3.match, "xest") == 0);
    mu_assert("Partial match left #2", m3.rest_left == NULL);
    mu_assert("Partial match left #3", strcmp(m3.rest_right, "er") == 0);
    mu_assert("Partial match left #4", match_type(m3) == PARTIAL_LEFT);

    Matching m4 = match("xester", "xest");
    mu_assert("Partial match left #5", strcmp(m4.match, "xest") == 0);
    mu_assert("Partial match left #6", m4.rest_right == NULL);
    mu_assert("Partial match left #7", strcmp(m4.rest_left, "er") == 0);
    mu_assert("Partial match left #8", match_type(m4) == PARTIAL_RIGHT);


    Matching m5 = match("a", "abaa");
    mu_assert("Match", strcmp(m5.match, "a") == 0);



    return NULL;
}

char *test_matching()
{
    mu_run_utest(utest_matching_match);
    return NULL;
}
