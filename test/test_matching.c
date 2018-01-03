#include "test.h"
#include "matching.h"

char *utest_matching_match()
{
    Matching m0 = match(label("xest"), label("test"));
    mu_assert("No match #1", match_type(m0) == NONE);

    Matching m = match(label("test"), label("xest"));
    mu_assert("No match #2", match_type(m) == NONE);

    Matching m2 = match(label("xest"), label("xest"));
    mu_assert("Exact match 1", m2.size == 4);
    mu_assert("Exact match 2", m2.left == 0);
    mu_assert("Exact match 3", m2.right == 0);
    mu_assert("Exact match 4", match_type(m2) == EXACT);

    Matching m3 = match(label("xest"), label("xester"));
    mu_assert("Partial match left #1", m3.size == 4);
    mu_assert("Partial match left #2", m3.left == 0);
    mu_assert("Partial match left #3", m3.right == 2);
    mu_assert("Partial match left #4", match_type(m3) == PARTIAL_RIGHT);

    Matching m4 = match(label("xester"), label("xest"));
    mu_assert("Partial match left #5", m4.size == 4);
    mu_assert("Partial match left #6", m4.right == 0);
    mu_assert("Partial match left #7", m4.left == 2);
    mu_assert("Partial match left #8", match_type(m4) == PARTIAL_LEFT);


    Matching m5 = match(label("a"), label("abaa"));
    mu_assert("Match", m5.size == 1);

    Matching m6 = match(label("he"), label(""));
    Matching m7 = match(label(""), label("he"));

    mu_assert("Partial match #9", match_type(m6) == PARTIAL_LEFT);
    mu_assert("Partial match #10", match_type(m7) == PARTIAL_RIGHT);

    // Considered partial left. Not a situation that occurs in the algorithm
    Matching m8 = match(label("abcde"), label("abcxx"));
    mu_assert("Partial match #11", match_type(m8) == PARTIAL_LEFT);

    return NULL;
}

char *test_matching()
{
    mu_run_utest(utest_matching_match);
    return NULL;
}
