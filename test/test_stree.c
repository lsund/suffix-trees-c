
#include "test.h"
#include "stree.h"

char *utest_edge_match()
{
    EdgePointer a = edge_from_mark("xest");
    Matching m = edge_match_marking(a, "test");
    mu_assert("No match", match_type(m) == NONE);

    Matching m2 = edge_match_marking(a, "xest");
    mu_assert("Exact match", strcmp(m2.match, "xest") == 0);
    mu_assert("Exact match", m2.rest == NULL);
    mu_assert("Exact match", match_type(m2) == EXACT);

    Matching m3 = edge_match_marking(a, "xester");
    mu_assert("Partial match", strcmp(m3.match, "xest") == 0);
    mu_assert("Partial match", strcmp(m3.rest, "er") == 0);
    mu_assert("Partial match", match_type(m3) == PARTIAL);

    return NULL;
}

char *utest_stree_find()
{
    EdgePointer t = edge_from_mark("x");
    EdgePointer t2 = edge_from_mark("e");
    EdgePointer t3 = edge_from_mark("zy");
    EdgePointer t4 = edge_from_mark("zf");
    stree_extend(t, t2);
    stree_extend(t2, t3);
    stree_extend(t2, t4);
    EdgePointer e = stree_find(t, "xezy");
    mu_assert("Find end #1", e);

    /* EdgePointer ab = edge_from_mark("ab"); */
    /* EdgePointer b = edge_from_mark("b"); */
    /* ab->right = b; */
    /* mu_assert("Find end #2", stree_find(b, "b")); */

    /* EdgePointer aba = edge_from_mark("aba"); */
    /* mu_assert("Find end #3", stree_find(aba, "a")); */

    return NULL;
}


char *test_stree()
{
    mu_run_utest(utest_edge_match);
    mu_run_utest(utest_stree_find);
    return NULL;
}
