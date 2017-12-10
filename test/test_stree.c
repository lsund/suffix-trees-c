
#include "test.h"
#include "stree.h"

char *utest_edge_match_marking()
{
    Label l = label("test", 2);
    EdgePointer a = edge_from_label(l);

    mu_assert("Blah", edge_match_marking(a, "t") == 0);

    return NULL;
}


char *test_stree()
{
    mu_run_utest(utest_edge_match_marking);
    return NULL;
}
