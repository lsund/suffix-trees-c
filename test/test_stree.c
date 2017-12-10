
#include "test.h"
#include "stree.h"

char *utest_edge_match_marking()
{
    EdgePointer a = edge_from_mark("xest", 2);
    mu_assert("No match", edge_match_marking(a, "test").match == NULL);
    mu_assert("No match", edge_match_marking(a, "test").rest == NULL);
    mu_assert("Exact match", strcmp(edge_match_marking(a, "xest").match, "xest") == 0);
    mu_assert("Exact match", edge_match_marking(a, "xest").rest == NULL);
    mu_assert("Partial match", strcmp(edge_match_marking(a, "xe").match, "xe") == 0);
    mu_assert("Partial match", strcmp(edge_match_marking(a, "xe").rest, "st") == 0);

    return NULL;
}


char *test_stree()
{
    mu_run_utest(utest_edge_match_marking);
    return NULL;
}
