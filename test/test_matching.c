#include "test.h"
#include "matching.h"

char *utest_matching_match()
{
    Matching m0 = match("xest", "test");
    mu_assert("No match #1", match_type(m0) == NONE);

    Matching m = match("test", "xest");
    mu_assert("No match #2", match_type(m) == NONE);

    Matching m2 = match("xest", "xest");
    mu_assert("Exact match 1", m2.match_both == 4);
    mu_assert("Exact match 2", m2.unmatched_left == 0);
    mu_assert("Exact match 3", m2.unmatched_right == 0);
    mu_assert("Exact match 4", match_type(m2) == EXACT);

    Matching m3 = match("xest", "xester");
    mu_assert("Partial match left #1", m3.match_both == 4);
    mu_assert("Partial match left #2", m3.unmatched_left == 0);
    mu_assert("Partial match left #3", m3.unmatched_right == 2);
    mu_assert("Partial match left #4", match_type(m3) == PARTIAL_RIGHT);

    Matching m4 = match("xester", "xest");
    mu_assert("Partial match left #5", m4.match_both == 4);
    mu_assert("Partial match left #6", m4.unmatched_right == 0);
    mu_assert("Partial match left #7", m4.unmatched_left == 2);
    mu_assert("Partial match left #8", match_type(m4) == PARTIAL_LEFT);


    Matching m5 = match("a", "abaa");
    mu_assert("Match", m5.match_both == 1);

    Matching m6 = match("he", "");
    Matching m7 = match("", "he");

    mu_assert("Partial match #9", match_type(m6) == PARTIAL_LEFT);
    mu_assert("Partial match #10", match_type(m7) == PARTIAL_RIGHT);

    return NULL;
}

char *test_matching()
{
    mu_run_utest(utest_matching_match);
    return NULL;
}
