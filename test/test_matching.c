#include "test.h"
#include "matching.h"


char *utest_matching_match_offset()
{
    Label l1 = label_full("test");
    Label l2 = label_full("abctest");
    Label l3 = label_full("te");
    Label l4 = label_full("abctestabc");

    Matching m0 = match(l1, l2);
    mu_assert("No offset #1", match_type(m0) == NONE);
    l2->i += 3;
    Matching m1 = match(l1, l2);
    mu_assert("offset #1", match_type(m1) == EXACT);
    Matching m2 = match(l3, l2);
    mu_assert("offset #2", match_type(m2) == PARTIAL_RIGHT);
    l4->j -= 3;
    l4->i += 3;
    Matching m3 = match(l4, l1);
    mu_assert("offset #3", match_type(m3) == EXACT);


    const char *text = "abcab";

    l1 = label(text, 0, 5);  // abcab
    l2  = label(text, 0, 2); // ab

    Matching m4 = match(l1, l2);
    mu_assert("Offset #4", match_type(m4) == PARTIAL_LEFT);

    m4 = match(l2, l1);
    mu_assert("Offset #5", match_type(m4) == PARTIAL_RIGHT);

    return NULL;
}

char *utest_matching_match()
{
    Matching m0 = match(label_full("xest"), label_full("test"));
    mu_assert("No match #1", match_type(m0) == NONE);

    Matching m = match(label_full("test"), label_full("xest"));
    mu_assert("No match #2", match_type(m) == NONE);

    Matching m2 = match(label_full("xest"), label_full("xest"));
    mu_assert("Exact match 1", m2.size == 4);
    mu_assert("Exact match 2", m2.left == 0);
    mu_assert("Exact match 3", m2.right == 0);
    mu_assert("Exact match 4", match_type(m2) == EXACT);

    Matching m3 = match(label_full("xest"), label_full("xester"));
    mu_assert("Partial match left #1", m3.size == 4);
    mu_assert("Partial match left #2", m3.left == 0);
    mu_assert("Partial match left #3", m3.right == 2);
    mu_assert("Partial match left #4", match_type(m3) == PARTIAL_RIGHT);

    Matching m4 = match(label_full("xester"), label_full("xest"));
    mu_assert("Partial match left #5", m4.size == 4);
    mu_assert("Partial match left #6", m4.right == 0);
    mu_assert("Partial match left #7", m4.left == 2);
    mu_assert("Partial match left #8", match_type(m4) == PARTIAL_LEFT);


    Matching m5 = match(label_full("a"), label_full("abaa"));
    mu_assert("Match", m5.size == 1);

    Matching m6 = match(label_full("he"), label_full(""));
    Matching m7 = match(label_full(""), label_full("he"));

    mu_assert("Partial match #9", match_type(m6) == PARTIAL_LEFT);
    mu_assert("Partial match #10", match_type(m7) == PARTIAL_RIGHT);

    // Considered partial left. Not a situation that occurs in the algorithm
    Matching m8 = match(label_full("abcde"), label_full("abcxx"));
    mu_assert("Partial match #11", match_type(m8) == PARTIAL_LEFT);

    return NULL;
}

char *test_matching()
{
    mu_run_utest(utest_matching_match);
    mu_run_utest(utest_matching_match_offset);
    return NULL;
}
