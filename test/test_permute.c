
#include "test.h"
#include "stree.h"
#include "stree_permute.h"
#include "reader.h"
#include "stree_compare.h"
#include "vertex_ukkonen.h"

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

char *utest_stree_permute2()
{
    char tmp[64];
    char *text = "aba";

    // Flip a 2-branching tree
    STree2 t1 = ukkonen_naive2(text);

    stree_permute2(t1, 1);

    Vertex r = t1->r;

    label_mark2(tmp, r->c->l, text);
    mu_assert("Permuted tree #1", strcmp(tmp, "ba") == 0);
    label_mark2(tmp, r->c->s->l, text);
    mu_assert("Permuted tree #2", strcmp(tmp, "aba") == 0);
    mu_assert("Permuted tree #4", !r->c->s->s);

    // Flip back
    stree_permute2(t1, 1);
    label_mark2(tmp, r->c->l, text);
    mu_assert("Permuted tree #5", strcmp(tmp, "aba") == 0);
    label_mark2(tmp, r->c->s->l, text);
    mu_assert("Permuted tree #6", strcmp(tmp, "ba") == 0);
    mu_assert("Permuted tree #7", !r->c->s->s);

    // Flip with ID
    stree_permute2(t1, 0);

    label_mark2(tmp, r->c->l, text);
    mu_assert("Permuted tree #8", strcmp(tmp, "aba") == 0);
    label_mark2(tmp, r->c->s->l, text);
    mu_assert("Permuted tree #9", strcmp(tmp, "ba") == 0);
    mu_assert("Permuted tree #10", !r->c->s->s);

    // Flip a 2 branching tree, with depth 3

    text = "abaa";

    // Flip a 2-branching tree
    t1 = ukkonen_naive2(text);

    stree_permute2(t1, 1);

    r = t1->r;

    label_mark2(tmp, r->c->l, text);
    mu_assert("Permuted tree #11", strcmp(tmp, "baa") == 0);
    label_mark2(tmp, r->c->s->l, text);
    mu_assert("Permuted tree #12", strcmp(tmp, "a") == 0);
    mu_assert("Permuted tree #13", !r->c->s->s);
    label_mark2(tmp, r->c->s->c->l, text);
    mu_assert("Permuted tree #14", strcmp(tmp, "baa") == 0);
    label_mark2(tmp, r->c->s->c->s->l, text);
    mu_assert("Permuted tree #15", strcmp(tmp, "a") == 0);

    // Flip back
    stree_permute2(t1, 1);
    label_mark2(tmp, r->c->l, text);
    mu_assert("Permuted tree #16", strcmp(tmp, "a") == 0);
    label_mark2(tmp, r->c->s->l, text);
    mu_assert("Permuted tree #17", strcmp(tmp, "baa") == 0);
    mu_assert("Permuted tree #18", !r->c->s->s);
    label_mark2(tmp, r->c->c->l, text);
    mu_assert("Permuted tree #19", strcmp(tmp, "baa") == 0);
    label_mark2(tmp, r->c->c->s->l, text);
    mu_assert("Permuted tree #20", strcmp(tmp, "a") == 0);

    // Flip the lower part
    vertex_permute(r->c, 1);
    label_mark2(tmp, r->c->l, text);
    mu_assert("Permuted tree #21", strcmp(tmp, "a") == 0);
    label_mark2(tmp, r->c->s->l, text);
    mu_assert("Permuted tree #22", strcmp(tmp, "baa") == 0);
    mu_assert("Permuted tree #23", !r->c->s->s);
    label_mark2(tmp, r->c->c->l, text);
    mu_assert("Permuted tree #24", strcmp(tmp, "a") == 0);
    label_mark2(tmp, r->c->c->s->l, text);
    mu_assert("Permuted tree #25", strcmp(tmp, "baa") == 0);

    // Flip back
    vertex_permute(r->c, 1);
    label_mark2(tmp, r->c->l, text);
    mu_assert("Permuted tree #26", strcmp(tmp, "a") == 0);
    label_mark2(tmp, r->c->s->l, text);
    mu_assert("Permuted tree #27", strcmp(tmp, "baa") == 0);
    mu_assert("Permuted tree #28", !r->c->s->s);
    label_mark2(tmp, r->c->c->l, text);
    mu_assert("Permuted tree #29", strcmp(tmp, "baa") == 0);
    label_mark2(tmp, r->c->c->s->l, text);
    mu_assert("Permuted tree #30", strcmp(tmp, "a") == 0);

    // Flip leaf, should not change anything
    vertex_permute(r->c->c, 1);
    label_mark2(tmp, r->c->l, text);
    mu_assert("Permuted tree #31", strcmp(tmp, "a") == 0);
    label_mark2(tmp, r->c->s->l, text);
    mu_assert("Permuted tree #32", strcmp(tmp, "baa") == 0);
    mu_assert("Permuted tree #33", !r->c->s->s);
    label_mark2(tmp, r->c->c->l, text);
    mu_assert("Permuted tree #34", strcmp(tmp, "baa") == 0);
    label_mark2(tmp, r->c->c->s->l, text);
    mu_assert("Permuted tree #35", strcmp(tmp, "a") == 0);

    text = "abc";

    t1 = ukkonen_naive2(text);
    r = t1->r;

    label_mark2(tmp, r->c->l, text);
    mu_assert("Permuted tree #36", strcmp(tmp, "abc") == 0);
    label_mark2(tmp, r->c->s->l, text);
    mu_assert("Permuted tree #37", strcmp(tmp, "bc") == 0);
    label_mark2(tmp, r->c->s->s->l, text);
    mu_assert("Permuted tree #38", strcmp(tmp, "c") == 0);


    //                  0   1   2   3   4   5
    // 3 permutations: 012 021 102 120 210 201
    stree_permute2(t1, 1);
    label_mark2(tmp, r->c->l, text);
    mu_assert("Permuted tree #39", strcmp(tmp, "abc") == 0);
    label_mark2(tmp, r->c->s->l, text);
    mu_assert("Permuted tree #40", strcmp(tmp, "c") == 0);
    label_mark2(tmp, r->c->s->s->l, text);
    mu_assert("Permuted tree #41", strcmp(tmp, "bc") == 0);


    // Flip back
    stree_permute2(t1, 1);
    label_mark2(tmp, r->c->l, text);
    mu_assert("Permuted tree #42", strcmp(tmp, "abc") == 0);
    label_mark2(tmp, r->c->s->l, text);
    mu_assert("Permuted tree #43", strcmp(tmp, "bc") == 0);
    label_mark2(tmp, r->c->s->s->l, text);
    mu_assert("Permuted tree #44", strcmp(tmp, "c") == 0);

    stree_permute2(t1, 4);
    label_mark2(tmp, r->c->l, text);
    mu_assert("Permuted tree #44", strcmp(tmp, "c") == 0);
    label_mark2(tmp, r->c->s->l, text);
    mu_assert("Permuted tree #43", strcmp(tmp, "bc") == 0);
    label_mark2(tmp, r->c->s->s->l, text);
    mu_assert("Permuted tree #42", strcmp(tmp, "abc") == 0);



    // Tree should stay the same when permuted twice
    free(t1);
    t1 = ukkonen_naive2(text);
    r = t1->r;
    char *s = "r[<0,3,0>[],<1,3,1>[],<2,3,2>[]]";
    STree2 t2 = stree_init2(text);
    read2(s, t2);
    stree_permute2(t1, 0);
    stree_permute2(t1, permutation_inverse_number(0, 3));
    mu_assert("Perumted tree #43", stree_equals2(t1, t2));
    stree_permute2(t1, 1);
    stree_permute2(t1, permutation_inverse_number(1, 3));
    mu_assert("Perumted tree #40", stree_equals2(t1, t2));
    stree_permute2(t1, 2);
    stree_permute2(t1, permutation_inverse_number(2, 3));
    mu_assert("Perumted tree #41", stree_equals2(t1, t2));
    stree_permute2(t1, 3);
    stree_permute2(t1, permutation_inverse_number(3, 3));
    mu_assert("Perumted tree #41", stree_equals2(t1, t2));
    stree_permute2(t1, 4);
    stree_permute2(t1, permutation_inverse_number(4, 3));
    mu_assert("Perumted tree #41", stree_equals2(t1, t2));
    stree_permute2(t1, 5);
    stree_permute2(t1, permutation_inverse_number(5, 3));
    mu_assert("Perumted tree #41", stree_equals2(t1, t2));


    return NULL;
}

char *test_stree_permute()
{
    mu_run_utest(utest_stree_permute);
    mu_run_utest(utest_stree_permute2);
    return NULL;
}
