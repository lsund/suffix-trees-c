
#include "test.h"
#include "stree.h"

char *utest_stree_find()
{
    EdgePointer t = edge_from_string("he");
    EdgePointer t2 = edge_from_string("ll");
    EdgePointer t3 = edge_from_string("o");
    EdgePointer t4 = edge_from_string("as");
    EdgePointer t5 = edge_from_string("j");
    stree_extend(t, t2);
    stree_extend(t2, t3);
    stree_extend(t2, t4);
    stree_extend(t, t5);

    TreeMatching tm = stree_find(t, "he");
    TreeMatching tm1 = stree_find(t, "h");
    TreeMatching tm2 = stree_find(t, "hej");
    TreeMatching tm3 = stree_find(t, "hello");
    TreeMatching tm4 = stree_find(t, "hellas");
    TreeMatching tm5 = stree_find(t, "hel");
    TreeMatching tm6 = stree_find(t, "hella");
    TreeMatching tm7 = stree_find(t, "");

    mu_assert("End should exist #1", tm.tree);
    mu_assert("End should exist #2", tm1.tree);
    mu_assert("End should exist #3", tm2.tree);
    mu_assert("End should exist #4", tm3.tree);
    mu_assert("End should exist #5", tm4.tree);
    mu_assert("End should exist #6", tm5.tree);
    mu_assert("End should exist #7", tm6.tree);
    mu_assert("End should exist #8", tm7.tree);

    mu_assert("control of label #1", strcmp(tm.tree->lbl->mark, "he") == 0);
    mu_assert("control of label #2", strcmp(tm1.tree->lbl->mark, "he") == 0);
    mu_assert("control of label #3", strcmp(tm2.tree->lbl->mark, "j") == 0);
    mu_assert("control of label #4", strcmp(tm3.tree->lbl->mark, "o") == 0);
    mu_assert("control of label #5", strcmp(tm4.tree->lbl->mark, "as") == 0);
    mu_assert("control of label #6", strcmp(tm5.tree->lbl->mark, "ll") == 0);
    mu_assert("control of label #7", strcmp(tm6.tree->lbl->mark, "as") == 0);
    mu_assert("control of label #8", strcmp(tm7.tree->lbl->mark, "he") == 0);

    return NULL;
}


char *test_stree()
{
    mu_run_utest(utest_stree_find);
    return NULL;
}
