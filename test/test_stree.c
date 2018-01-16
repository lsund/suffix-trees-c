
#include "test.h"
#include "stree.h"
#include "edge.h"


char *utest_stree_es_with()
{
    char *text = "abcd";
    Edge t1 = edge(text, 0, 1);
    Edge t2 = edge(text, 1, 2);
    Edge t3 = edge(text, 2, 3);
    Edge t4 = edge(text, 3, 4);

    stree_extend_edge_sibling(t1, t2);
    stree_extend_edge_sibling(t1, t3);
    stree_extend_edge_sibling(t1, t4);

    mu_assert("Branches 1", stree_es_with(t1, 'a'));
    mu_assert("Branches 2", stree_es_with(t1, 'b'));
    mu_assert("Branches 3", stree_es_with(t1, 'c'));
    mu_assert("Branches 4", stree_es_with(t1, 'd'));
    mu_assert("Branches 5", !stree_es_with(t1, 'e'));
    mu_assert("Branches 6", stree_es_with(t2, 'c'));
    return NULL;
}

char *utest_stree_find()
{
    char *text = "helloasj";
    Edge t1 = edge(text, 0, 2);
    Edge t2 = edge(text, 2, 4);
    Edge t3 = edge(text, 4, 5);
    Edge t4 = edge(text, 5, 7);
    Edge t5 = edge(text, 7, 8);
    stree_extend_edge_below(t1, t2);
    stree_extend_edge_below(t2, t3);
    stree_extend_edge_below(t2, t4);
    stree_extend_edge_below(t1, t5);

    TreeMatching tm0 = stree_find(t1,label_full("he"));
    TreeMatching tm1 = stree_find(t1,label_full("h"));
    TreeMatching tm2 = stree_find(t1,label_full("hej"));
    TreeMatching tm3 = stree_find(t1,label_full("hello"));
    TreeMatching tm4 = stree_find(t1,label_full("hellas"));
    TreeMatching tm5 = stree_find(t1,label_full("hel"));
    TreeMatching tm6 = stree_find(t1,label_full("hella"));
    TreeMatching tm7 = stree_find(t1,label_full(""));

    mu_assert("End should exist #1", tm0.end);
    mu_assert("End should exist #2", tm1.end);
    mu_assert("End should exist #3", tm2.end);
    mu_assert("End should exist #4", tm3.end);
    mu_assert("End should exist #5", tm4.end);
    mu_assert("End should exist #6", tm5.end);
    mu_assert("End should exist #7", tm6.end);
    mu_assert("End should exist #8", tm7.end);

    char tmp[64];
    label_mark(tm0.end->l, tmp);
    mu_assert("control of label #1", strcmp(tmp, "he") == 0);
    label_mark(tm1.end->l, tmp);
    mu_assert("control of label #2", strcmp(tmp, "he") == 0);
    label_mark(tm2.end->l, tmp);
    mu_assert("control of label #3", strcmp(tmp, "j") == 0);
    label_mark(tm3.end->l, tmp);
    mu_assert("control of label #4", strcmp(tmp, "o") == 0);
    label_mark(tm4.end->l, tmp);
    mu_assert("control of label #5", strcmp(tmp, "as") == 0);
    label_mark(tm5.end->l, tmp);
    mu_assert("control of label #6", strcmp(tmp, "ll") == 0);
    label_mark(tm6.end->l, tmp);
    mu_assert("control of label #7", strcmp(tmp, "as") == 0);
    label_mark(tm7.end->l, tmp);
    mu_assert("control of label #8", strcmp(tmp, "he") == 0);

    return NULL;
}


char *utest_stree_swap()
{
    char tmp[64];
    char *text = "abcdef";

    // Flip a 3-node tree
    Edge t1 = edge("r", 0, 1);
    Edge t2 = edge(text, 0, 1);
    Edge t3 = edge(text, 1, 2);
    stree_extend_edge_below(t1, t2);
    stree_extend_edge_sibling(t2, t3);

    stree_permute(t1, 1);

    label_mark(t1->l, tmp);
    mu_assert("Permuted tree #1", strcmp(tmp, "r") == 0);

    label_mark(t1->ec->l, tmp);
    mu_assert("Permuted tree #2", strcmp(tmp, "b") == 0);

    label_mark(t1->ec->es->l, tmp);
    mu_assert("Permuted tree #3", strcmp(tmp, "a") == 0);

    mu_assert("Permuted tree #4", !t1->ec->es->es);

    // No swap of a 3-node tree
    t1 = edge("r", 0, 1);
    t2 = edge(text, 0, 1);
    t3 = edge(text, 1, 2);
    stree_extend_edge_below(t1, t2);
    stree_extend_edge_sibling(t2, t3);
    stree_permute(t1, 0);

    label_mark(t1->l, tmp);
    mu_assert("Permuted tree #5", strcmp(tmp, "r") == 0);

    label_mark(t1->ec->l, tmp);
    mu_assert("Permuted tree #6", strcmp(tmp, "a") == 0);

    label_mark(t1->ec->es->l, tmp);
    mu_assert("Permuted tree #7", strcmp(tmp, "b") == 0);

    mu_assert("Permuted tree #8", !t1->ec->es->es);

    // abcdef
    // Flip a 7-node tree
    t1 = edge("r", 0, 1);
    Edge ta = edge(text, 0, 1);
    Edge tb = edge(text, 1, 2);
    Edge tc = edge(text, 2, 3);
    Edge td = edge(text, 3, 4);
    Edge te = edge(text, 4, 5);
    Edge tf = edge(text, 5, 6);
    stree_extend_edge_below(t1, ta);
    stree_extend_edge_sibling(ta, tb);
    stree_extend_edge_below(ta, tc);
    stree_extend_edge_sibling(tc, td);
    stree_extend_edge_below(tb, te);
    stree_extend_edge_sibling(te, tf);
    stree_permute(t1, 1);

    label_mark(t1->l, tmp);
    mu_assert("Permuted tree #5", strcmp(tmp, "r") == 0);

    label_mark(t1->ec->l, tmp);
    mu_assert("Permuted tree #6", strcmp(tmp, "b") == 0);

    label_mark(t1->ec->es->l, tmp);
    mu_assert("Permuted tree #7", strcmp(tmp, "a") == 0);

    mu_assert("Permuted tree #8", !t1->ec->es->es);

    label_mark(t1->ec->ec->l, tmp);
    mu_assert("Permuted tree #9", strcmp(tmp, "e") == 0);

    label_mark(t1->ec->ec->es->l, tmp);
    mu_assert("Permuted tree #9", strcmp(tmp, "f") == 0);

    label_mark(t1->ec->es->ec->l, tmp);
    mu_assert("Permuted tree #9", strcmp(tmp, "c") == 0);

    label_mark(t1->ec->es->ec->es->l, tmp);
    mu_assert("Permuted tree #9", strcmp(tmp, "d") == 0);
    return NULL;
}


char *test_stree()
{
    mu_run_utest(utest_stree_find);
    mu_run_utest(utest_stree_es_with);
    mu_run_utest(utest_stree_swap);
    return NULL;
}
