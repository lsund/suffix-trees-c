
#include "test.h"
#include "stree.h"
#include "edge.h"


char *utest_stree_sibling_with()
{
    char *text = "abcd";
    Edge t1 = edge(text, 0, 1);
    Edge t2 = edge(text, 1, 2);
    Edge t3 = edge(text, 2, 3);
    Edge t4 = edge(text, 3, 4);

    stree_extend_edge_sibling(t1, t2);
    stree_extend_edge_sibling(t1, t3);
    stree_extend_edge_sibling(t1, t4);

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

    // Flip a 2-branching tree
    Edge r = edge("r", 0, 1);
    Edge a = edge(text, 0, 1);
    Edge b = edge(text, 1, 2);
    stree_extend_edge_below(r, a);
    stree_extend_edge_sibling(a, b);

    stree_permute(r, 1);

    label_mark(r->l, tmp);
    mu_assert("Permuted tree #1", strcmp(tmp, "r") == 0);
    label_mark(r->c->l, tmp);
    mu_assert("Permuted tree #2", strcmp(tmp, "b") == 0);
    label_mark(r->c->s->l, tmp);
    mu_assert("Permuted tree #3", strcmp(tmp, "a") == 0);
    mu_assert("Permuted tree #4", !r->c->s->s);

    // Flip back
    stree_permute(r, 1);
    label_mark(r->l, tmp);
    mu_assert("Permuted tree #5", strcmp(tmp, "r") == 0);
    label_mark(r->c->l, tmp);
    mu_assert("Permuted tree #6", strcmp(tmp, "a") == 0);
    label_mark(r->c->s->l, tmp);
    mu_assert("Permuted tree #7", strcmp(tmp, "b") == 0);

    mu_assert("Permuted tree #8", !r->c->s->s);

    // Flip with ID
    stree_permute(r, 0);
    label_mark(r->l, tmp);
    mu_assert("Permuted tree #9", strcmp(tmp, "r") == 0);
    label_mark(r->c->l, tmp);
    mu_assert("Permuted tree #10", strcmp(tmp, "a") == 0);
    label_mark(r->c->s->l, tmp);
    mu_assert("Permuted tree #11", strcmp(tmp, "b") == 0);
    mu_assert("Permuted tree #12", !r->c->s->s);

    // Flip a 2 branching tree, with depth 3
    Edge c = edge(text, 2, 3);
    Edge d = edge(text, 3, 4);
    Edge e = edge(text, 4, 5);
    Edge f = edge(text, 5, 6);
    stree_extend_edge_below(a, c);
    stree_extend_edge_sibling(c, d);
    stree_extend_edge_below(b, e);
    stree_extend_edge_sibling(e, f);

    stree_permute(r, 1);

    label_mark(r->l, tmp);
    mu_assert("Permuted tree #13", strcmp(tmp, "r") == 0);
    label_mark(r->c->l, tmp);
    mu_assert("Permuted tree #14", strcmp(tmp, "b") == 0);
    label_mark(r->c->s->l, tmp);
    mu_assert("Permuted tree #15", strcmp(tmp, "a") == 0);
    mu_assert("Permuted tree #16", !r->c->s->s);
    label_mark(r->c->c->l, tmp);
    mu_assert("Permuted tree #17", strcmp(tmp, "e") == 0);
    label_mark(r->c->c->s->l, tmp);
    mu_assert("Permuted tree #18", strcmp(tmp, "f") == 0);
    label_mark(r->c->s->c->l, tmp);
    mu_assert("Permuted tree #19", strcmp(tmp, "c") == 0);
    label_mark(r->c->s->c->s->l, tmp);
    mu_assert("Permuted tree #20", strcmp(tmp, "d") == 0);

    // Flip lower right part of 7-node tree
    stree_permute(b, 1);
    label_mark(r->l, tmp);
    mu_assert("Permuted tree #21", strcmp(tmp, "r") == 0);
    label_mark(r->c->l, tmp);
    mu_assert("Permuted tree #22", strcmp(tmp, "b") == 0);
    label_mark(r->c->s->l, tmp);
    mu_assert("Permuted tree #23", strcmp(tmp, "a") == 0);
    mu_assert("Permuted tree #24", !r->c->s->s);
    label_mark(r->c->c->l, tmp);
    mu_assert("Permuted tree #25", strcmp(tmp, "f") == 0);
    label_mark(r->c->c->s->l, tmp);
    mu_assert("Permuted tree #26", strcmp(tmp, "e") == 0);
    label_mark(r->c->s->c->l, tmp);
    mu_assert("Permuted tree #27", strcmp(tmp, "c") == 0);
    label_mark(r->c->s->c->s->l, tmp);
    mu_assert("Permuted tree #28", strcmp(tmp, "d") == 0);

    // Flip lower left part of 7-node tree
    stree_permute(a, 1);
    label_mark(r->l, tmp);
    mu_assert("Permuted tree #21", strcmp(tmp, "r") == 0);
    label_mark(r->c->l, tmp);
    mu_assert("Permuted tree #22", strcmp(tmp, "b") == 0);
    label_mark(r->c->s->l, tmp);
    mu_assert("Permuted tree #23", strcmp(tmp, "a") == 0);
    mu_assert("Permuted tree #24", !r->c->s->s);
    label_mark(r->c->c->l, tmp);
    mu_assert("Permuted tree #25", strcmp(tmp, "f") == 0);
    label_mark(r->c->c->s->l, tmp);
    mu_assert("Permuted tree #26", strcmp(tmp, "e") == 0);
    label_mark(r->c->s->c->l, tmp);
    mu_assert("Permuted tree #27", strcmp(tmp, "d") == 0);
    label_mark(r->c->s->c->s->l, tmp);
    mu_assert("Permuted tree #28", strcmp(tmp, "c") == 0);

    // Flip leaf edge
    stree_permute(f, 1);
    label_mark(r->l, tmp);
    mu_assert("Permuted tree #29", strcmp(tmp, "r") == 0);
    label_mark(r->c->l, tmp);
    mu_assert("Permuted tree #30", strcmp(tmp, "b") == 0);
    label_mark(r->c->s->l, tmp);
    mu_assert("Permuted tree #31", strcmp(tmp, "a") == 0);
    mu_assert("Permuted tree #32", !r->c->s->s);
    label_mark(r->c->c->l, tmp);
    mu_assert("Permuted tree #33", strcmp(tmp, "f") == 0);
    label_mark(r->c->c->s->l, tmp);
    mu_assert("Permuted tree #34", strcmp(tmp, "e") == 0);
    label_mark(r->c->s->c->l, tmp);
    mu_assert("Permuted tree #35", strcmp(tmp, "d") == 0);
    label_mark(r->c->s->c->s->l, tmp);
    mu_assert("Permuted tree #36", strcmp(tmp, "c") == 0);

    free(r);
    free(a);
    free(b);
    free(c);
    free(d);
    free(e);
    free(f);

    r = edge("r", 0, 1);
    a = edge(text, 0, 1);
    b = edge(text, 1, 2);
    c = edge(text, 2, 3);
    stree_extend_edge_below(r, a);
    stree_extend_edge_sibling(a, b);
    stree_extend_edge_sibling(b, c);

    //                  0   1   2   3   4   5
    // 3 permutations: 012 021 102 120 210 201
    stree_permute(r, 1);
    label_mark(r->l, tmp);
    mu_assert("Permuted tree #37", strcmp(tmp, "r") == 0);
    label_mark(r->c->l, tmp);
    mu_assert("Permuted tree #38", strcmp(tmp, "a") == 0);
    label_mark(r->c->s->l, tmp);
    mu_assert("Permuted tree #38", strcmp(tmp, "c") == 0);
    label_mark(r->c->s->s->l, tmp);
    mu_assert("Permuted tree #38", strcmp(tmp, "b") == 0);


    // Flip back
    stree_permute(r, 1);
    label_mark(r->l, tmp);
    mu_assert("Permuted tree #37", strcmp(tmp, "r") == 0);
    label_mark(r->c->l, tmp);
    mu_assert("Permuted tree #38", strcmp(tmp, "a") == 0);
    label_mark(r->c->s->l, tmp);
    mu_assert("Permuted tree #38", strcmp(tmp, "b") == 0);
    label_mark(r->c->s->s->l, tmp);
    mu_assert("Permuted tree #38", strcmp(tmp, "c") == 0);

    stree_permute(r, 4);
    label_mark(r->l, tmp);
    mu_assert("Permuted tree #37", strcmp(tmp, "r") == 0);
    label_mark(r->c->l, tmp);
    mu_assert("Permuted tree #38", strcmp(tmp, "c") == 0);
    label_mark(r->c->s->l, tmp);
    mu_assert("Permuted tree #38", strcmp(tmp, "b") == 0);
    label_mark(r->c->s->s->l, tmp);
    mu_assert("Permuted tree #38", strcmp(tmp, "a") == 0);

    return NULL;
}


char *test_stree()
{
    mu_run_utest(utest_stree_find);
    mu_run_utest(utest_stree_sibling_with);
    mu_run_utest(utest_stree_swap);
    return NULL;
}
