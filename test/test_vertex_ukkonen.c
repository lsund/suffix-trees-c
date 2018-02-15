#include "test.h"
#include "vertex_ukkonen.h"
#include "reader.h"
#include "writer.h"
#include "stree_compare.h"


static char *utest_adv_alg_example()
{
    STree2 tree, actual_tree;
    char *input, *s_actual;
    char s[STRING_MAX_LEN];
    s[0] = '\0';

    input = "a";
    s_actual = "r[<0,1,0>[]]";
    tree = ukkonen_naive2(input);
    write2(s, tree);
    mu_assert("Should equal #1", strcmp(s_actual, s) == 0);

    s[0] = '\0';
    input = "ab";
    s_actual = "r[<0,2,0>[],<1,2,1>[]]";
    tree = ukkonen_naive2(input);
    write2(s, tree);
    mu_assert("Should equal #2", strcmp(s_actual, s) == 0);

    s[0] = '\0';
    input = "aba";
    s_actual = "r[<0,3,0>[],<1,3,1>[]]";
    tree = ukkonen_naive2(input);
    write2(s, tree);
    mu_assert("Should equal #3", strcmp(s_actual, s) == 0);

    s[0] = '\0';
    input = "abaa";
    s_actual = "r[<0,1,-1>[<1,4,0>[],<3,4,2>[]],<1,4,1>[]]";
    tree = ukkonen_naive2(input);
    write2(s, tree);
    mu_assert("Should equal #4", strcmp(s_actual, s) == 0);

    s[0] = '\0';
    input = "abaab";
    s_actual = "r[<0,1,-1>[<1,5,0>[],<3,5,2>[]],<1,5,1>[]]";
    tree = ukkonen_naive2(input);
    write2(s, tree);
    mu_assert("Should equal #5", strcmp(s_actual, s) == 0);

    s[0] = '\0';
    input = "abaaba";
    s_actual = "r[<0,1,-1>[<1,6,0>[],<3,6,2>[]],<1,6,1>[]]";
    tree = ukkonen_naive2(input);
    write2(s, tree);
    mu_assert("Should equal #6", strcmp(s_actual, s) == 0);

    s[0] = '\0';
    input = "abaabab";
    s_actual = "r[<0,1,-1>[<1,3,-1>[<3,7,0>[],<6,7,3>[]],<3,7,2>[]],<1,3,-1>[<3,7,1>[],<6,7,4>[]]]";

    tree = ukkonen_naive2(input);
    actual_tree = stree_init2(input);
    write2(s, tree);
    read2(s_actual, actual_tree);

    mu_assert("Should be isomorphic #1", stree_isomorphic2(tree, actual_tree));

    s[0] = '\0';
    input = "abaababa";
    s_actual = "r[<0,1,-1>[<1,3,-1>[<3,8,0>[],<6,8,3>[]],<3,8,2>[]],<1,3,-1>[<3,8,1>[],<6,8,4>[]]]";
    tree = ukkonen_naive2(input);
    actual_tree = stree_init2(input);
    read2(s_actual, actual_tree);
    char tmp[500];
    tmp[0] = 0;
    write2(tmp, tree);

    mu_assert("Should be isomorphic #2", stree_isomorphic2(tree, actual_tree));

    Vertex el, ell, elll, elr, ellr, er, err, erl;

    el   = tree->r->c;
    ell  = tree->r->c->c;
    elll = tree->r->c->c->c;
    ellr = tree->r->c->c->c->s;
    elr  = tree->r->c->c->s;
    er   = tree->r->c->s;
    err  = tree->r->c->s->c->s;
    erl  = tree->r->c->s->c;

    vertex_mark(tmp, el, input);
    mu_assert("Local inspect #1", strcmp(tmp, "a") == 0);
    vertex_mark(tmp, ell, input);
    mu_assert("Local inspect #2", strcmp(tmp, "ba") == 0);
    vertex_mark(tmp, elll, input);
    mu_assert("Local inspect #2", strcmp(tmp, "ababa") == 0);
    vertex_mark(tmp, ellr, input);
    mu_assert("Local inspect #2", strcmp(tmp, "ba") == 0);
    vertex_mark(tmp, elr, input);
    mu_assert("Local inspect #2", strcmp(tmp, "ababa") == 0);
    vertex_mark(tmp, er, input);
    mu_assert("Local inspect #5", strcmp(tmp, "ba") == 0);
    vertex_mark(tmp, erl, input);
    mu_assert("Local inspect #5", strcmp(tmp, "ababa") == 0);
    vertex_mark(tmp, err, input);
    mu_assert("Local inspect #5", strcmp(tmp, "ba") == 0);

    mu_assert("Local inspect #9", el->k == -1);
    mu_assert("Local inspect #10", ell->k == -1);
    mu_assert("Local inspect #11", elll->k == 0);
    mu_assert("Local inspect #12", ellr->k == 3);
    mu_assert("Local inspect #13", elr->k == 2);
    mu_assert("Local inspect #14", er->k == -1);
    mu_assert("Local inspect #15", erl->k == 1);
    mu_assert("Local inspect #16", err->k == 4);

    return NULL;
}


static char *utest_stefan_kurz_example()
{
    STree2 tree, actual_tree;
    char *input, *s_actual;
    char s[STRING_MAX_LEN];
    s[0] = '\0';

    input = "acbcabcac";
    s_actual = "r[<0,1,-1>[<5,9,4>[],<1,9,0>[]],<2,5,-1>[<2,7,2>[],<1,2,5>[]],<1,2,-1>[<0,1,-1>[<2,7,3>[],<1,2,6>[]],<1,9,1>[]]]";
    tree = ukkonen_naive2(input);
    write2(s, tree);
    actual_tree = stree_init2(input);
    read2(s_actual, actual_tree);
    mu_assert("Isomorphic #1", stree_isomorphic2(tree, actual_tree));

    return NULL;
}


char *test_vertex_ukkonen()
{
    mu_run_utest(utest_adv_alg_example);
    mu_run_utest(utest_stefan_kurz_example);
    return NULL;
}
