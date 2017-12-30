
#include "test.h"
#include "stree.h"


char *utest_stree_match_letter()
{
    /* EdgePointer t = edge_from_string("aab"); */
    /* stree_match_letter(t, 'a'); */
    return NULL;
}


char *utest_edge_split()
{
    EdgePointer t = edge_from_string("abaa");
    edge_split(t, "a");
    mu_assert("split 1", strcmp(t->lbl->mark, "a") == 0);
    mu_assert("split 2", strcmp(t->child->lbl->mark, "baa") == 0);
    return NULL;
}

char *utest_stree_sibling_with()
{
    EdgePointer t1 = edge_from_string("a");
    EdgePointer t2 = edge_from_string("b");
    EdgePointer t3 = edge_from_string("c");
    EdgePointer t4 = edge_from_string("d");

    stree_extend_edge_right(t1, t2);
    stree_extend_edge_right(t1, t3);
    stree_extend_edge_right(t1, t4);

    mu_assert("Branches 1", stree_sibling_with(t1, 'a'));
    mu_assert("Branches 2", stree_sibling_with(t1, 'b'));
    mu_assert("Branches 3", stree_sibling_with(t1, 'c'));
    mu_assert("Branches 4", stree_sibling_with(t1, 'd'));
    mu_assert("Branches 5", !stree_sibling_with(t1, 'e'));
    mu_assert("Branches 6", stree_sibling_with(t2, 'c'));
    return NULL;
}

char *utest_stree_find()
{
    EdgePointer t = edge_from_string("he");
    EdgePointer t2 = edge_from_string("ll");
    EdgePointer t3 = edge_from_string("o");
    EdgePointer t4 = edge_from_string("as");
    EdgePointer t5 = edge_from_string("j");
    stree_extend_edge_below(t, t2);
    stree_extend_edge_below(t2, t3);
    stree_extend_edge_below(t2, t4);
    stree_extend_edge_below(t, t5);

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
    mu_run_utest(utest_stree_sibling_with);
    mu_run_utest(utest_edge_split);
    return NULL;
}
