#include "test.h"
#include "writer.h"

char *utest_write()
{
    STree tree;
    char *s, *t;
    tree = stree_init("root");
    s = malloc(sizeof(char) * STRING_INIT_LEN * 5);
    write(tree, s);
    t = "r0[]";
    mu_assert("Should equal #1", strcmp(s, t) == 0);
    free(s);

    stree_extend_edge_below(tree, edge_from_string("a"));
    s = malloc(sizeof(char) * STRING_INIT_LEN * 5);
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
