
#include "test.h"
#include "stree.h"
#include "edge.h"
#include "reader.h"
#include "writer.h"
#include "permute.h"
#include "stree_compare.h"

static int symmetric_isomorphic(STree t1, STree t2)
{
    return stree_isomorphic(t1, t2) && stree_isomorphic(t2, t1);
}

char *utest_stree_isomorphic()
{
    STree t1, t2, t3, t4, t5, t6, t7, t8, t9;
    char *s1, *s2, *s3, *s4, *s5, *s6, *s7, *s8, *s9;

    // These are isomorphic
    s1 = "root[a1[],b2[]]";
    s2 = "root[b2[],a1[]]";
    s3 = "root[b3[],a1[]]";

    // This is not
    s4 = "root[c3[],a1[]]";

    // These are isomorphic
    s5 = "root[b1[],a2[],c3[]]";
    s6 = "root[a1[],c2[],b3[]]";
    s7 = "root[c1[],b2[],a3[]]";
    s8 = "root[c1[],a2[],b3[]]";

    // This is not
    s9 = "root[c1[],c2[],b3[]]";

    read(s1, &t1);
    read(s2, &t2);
    read(s3, &t3);
    read(s4, &t4);
    read(s5, &t5);
    read(s6, &t6);
    read(s7, &t7);
    read(s8, &t8);
    read(s9, &t9);

    /* mu_assert("Isomorphic #1", symmetric_isomorphic(t1, t2)); */
    /* mu_assert("Isomorphic #3", symmetric_isomorphic(t2, t2)); */
    /* mu_assert("Isomorphic #5", symmetric_isomorphic(t1, t3)); */
    /* mu_assert("Isomorphic #6", !stree_isomorphic(t1, t4)); */

    /* mu_assert("Isomorphic #7", symmetric_isomorphic(t5, t6)); */
    /* mu_assert("Isomorphic #9", symmetric_isomorphic(t5, t7)); */
    /* mu_assert("Isomorphic #10", symmetric_isomorphic(t5, t8)); */
    /* mu_assert("Isomorphic #11", symmetric_isomorphic(t6, t7)); */
    /* mu_assert("Isomorphic #12", symmetric_isomorphic(t6, t8)); */
    /* mu_assert("Isomorphic #13", symmetric_isomorphic(t7, t8)); */
    /* mu_assert("Isomorphic #14", !stree_isomorphic(t8, t9)); */
    /* mu_assert("Isomorphic #15", !stree_isomorphic(t5, t9)); */
    /* mu_assert("Isomorphic #16", !stree_isomorphic(t9, t6)); */

    // Depth 2
    // These are isomorphic
    s1 = "root[a1[c3[],d4[]],b2[]]";
    s3 = "root[b2[],a1[d4[],c3[]]]";
    s2 = "root[a1[d4[],c3[]],b2[]]";

    s4 = "root[a1[x4[],c3[]],b2[]]";
    read(s1, &t1);
    read(s2, &t2);
    read(s3, &t3);
    read(s4, &t4);
    mu_assert("Isomorphic #17", symmetric_isomorphic(t1, t2));
    mu_assert("Isomorphic #18", symmetric_isomorphic(t1, t3));
    mu_assert("Isomorphic #19", !stree_isomorphic(t1, t4));

    return NULL;
}


char *utest_stree_equals()
{
    STree t1, t2, t3, t4;

    char *s1, *s2, *s3, *s4;
    s1 = "root[a1[],b2[]]";
    s2 = "root[b5[],a2[]]";
    s3 = "root[b1[]]";
    s4 = "root[b5[],a2[c3[]]]";

    char t[STRING_MAX_LEN];

    read(s1, &t1);
    read(s2, &t2);

    mu_assert("Equals #1", !stree_equals(t1, t2));
    mu_assert("Equals #2", stree_equals(t1, t1));
    mu_assert("Equals #3", stree_equals(t2, t2));
    mu_assert("Equals #4", !stree_equals(t2, t1));
    read(s1, &t2);
    mu_assert("Equals #5", stree_equals(t1, t2));
    read(s2, &t2);
    read(s3, &t3);

    write(t, t3);
    write(t, t2);
    mu_assert("Equals #6", !stree_equals(t2, t3));

    read(s4, &t4);
    mu_assert("Equals #7", !stree_equals(t2, t4));
    mu_assert("Equals #8", stree_equals(NULL, NULL));

    return NULL;
}


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

char *utest_scan_prefix()
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

    TreeMatching tm0 = scan_prefix(t1,label_full("he"));
    TreeMatching tm1 = scan_prefix(t1,label_full("h"));
    TreeMatching tm2 = scan_prefix(t1,label_full("hej"));
    TreeMatching tm3 = scan_prefix(t1,label_full("hello"));
    TreeMatching tm4 = scan_prefix(t1,label_full("hellas"));
    TreeMatching tm5 = scan_prefix(t1,label_full("hel"));
    TreeMatching tm6 = scan_prefix(t1,label_full("hella"));
    TreeMatching tm7 = scan_prefix(t1,label_full(""));

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


char *test_stree()
{
    mu_run_utest(utest_scan_prefix);
    mu_run_utest(utest_stree_sibling_with);
    mu_run_utest(utest_stree_permute);
    mu_run_utest(utest_stree_equals);
    mu_run_utest(utest_stree_isomorphic);
    return NULL;
}
