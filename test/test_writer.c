#include "test.h"
#include "writer.h"

char *utest_write()
{
    STree tree;
    char *t;

    char s[STRING_MAX_LEN];

    s[0] = '\0';
    tree = stree_init("root");
    write(s, tree);
    t = "r0[]";
    mu_assert("Should equal #1", strcmp(s, t) == 0);

    s[0] = '\0';
    stree_extend_edge_below(tree, edge("a", 0, 1));
    write(s, tree);
    t = "r[a0[]]";
    mu_assert("Should equal #2", strcmp(s, t) == 0);

    return NULL;
}


char *utest_write2()
{
    STree2 tree;
    char *t;

    char s[STRING_MAX_LEN];

    s[0] = '\0';
    tree = stree_init2("a");
    write2(s, tree);
    t = "r0[]";
    mu_assert("Should equal #1", strcmp(s, t) == 0);

    s[0] = '\0';
    stree_extend_below(tree, vertex(0, 1));
    write2(s, tree);
    t = "r[<0,1,0>[]]";
    mu_assert("Should equal #2", strcmp(s, t) == 0);

    return NULL;
}

char *test_writer()
{
    mu_run_utest(utest_write);
    mu_run_utest(utest_write2);
    return NULL;
}
