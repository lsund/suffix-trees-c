
#include "test.h"
#include "stree.h"
#include "stree_permute.h"
#include "reader.h"
#include "stree_compare.h"

char *utest_stree_permute()
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

    // Tree should stay the same when permuted twice
    char *s = "root[a1[],b2[],c3[]]";
    STree t, ta;
    read(s, &t);
    read(s, &ta);
    stree_permute(t, 0);
    stree_permute(t, permutation_inverse_number(0, 3));
    mu_assert("Perumted tree #39", stree_equals(t, ta));
    stree_permute(t, 1);
    stree_permute(t, permutation_inverse_number(1, 3));
    mu_assert("Perumted tree #40", stree_equals(t, ta));
    stree_permute(t, 2);
    stree_permute(t, permutation_inverse_number(2, 3));
    mu_assert("Perumted tree #41", stree_equals(t, ta));
    stree_permute(t, 3);
    stree_permute(t, permutation_inverse_number(3, 3));
    mu_assert("Perumted tree #42", stree_equals(t, ta));
    stree_permute(t, 4);
    stree_permute(t, permutation_inverse_number(4, 3));
    mu_assert("Perumted tree #43", stree_equals(t, ta));
    stree_permute(t, 5);
    stree_permute(t, permutation_inverse_number(5, 3));
    mu_assert("Perumted tree #44", stree_equals(t, ta));

    return NULL;
}

char *test_stree_permute()
{
    mu_run_utest(utest_stree_permute);
    return NULL;
}
