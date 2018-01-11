#include "test.h"
#include "writer.h"

char *utest_write()
{
    STree tree;
    char *t;

    char s[STRING_MAX_LEN];

    s[0] = '\0';
    tree = stree_init("root");
    write(tree, s);
    t = "r0[]";
    mu_assert("Should equal #1", strcmp(s, t) == 0);

    s[0] = '\0';
    stree_extend_edge_below(tree, edge("a", 0, 1));
    write(tree, s);
    t = "r[a0[]]";
    mu_assert("Should equal #2", strcmp(s, t) == 0);

    return NULL;
}


char *test_writer()
{
    mu_run_utest(utest_write);
    return NULL;
}
