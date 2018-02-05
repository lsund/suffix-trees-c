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

    actual_tree = stree_init2(s_actual);
    tree = ukkonen_naive2(input);
    write2(s, tree);
    read2(s_actual, actual_tree);

    /* mu_assert("Should be isomorphic #1", stree_isomorphic2(tree, actual_tree)); */

    s[0] = '\0';
    input = "abaababa";
    s_actual = "r[<0,1,-1>[<1,3,-1>[<3,8,0>[],<6,7,3>[]],<3,8,2>[]],<1,3,-1>[<3,8,1>[],<6,7,4>[]]]";
    tree = ukkonen_naive2(input);
    read2(s_actual, actual_tree);

    // TODO Continue here after testing isomorphic

    /* mu_assert("Should be isomorphic #2", stree_isomorphic2(tree, actual_tree)); */

    /* char l[74]; */

    /* Edge el, ell, elll, elr, ellr, er, err, erl; */

    /* el   = tree->c; */
    /* ell  = tree->c->c; */
    /* elll = tree->c->c->c; */
    /* ellr = tree->c->c->c->s; */
    /* elr  = tree->c->c->s; */
    /* er   = tree->c->s; */
    /* err  = tree->c->s->c->s; */
    /* erl  = tree->c->s->c; */

    /* edge_mark(el, l); */
    /* mu_assert("Local inspect #1", strcmp(l, "a") == 0); */
    /* edge_mark(ell, l); */
    /* mu_assert("Local inspect #2", strcmp(l, "ba") == 0); */
    /* edge_mark(elll, l); */
    /* mu_assert("Local inspect #3", strcmp(l, "ababa") == 0); */
    /* edge_mark(ellr, l); */
    /* mu_assert("Local inspect #4", strcmp(l, "ba") == 0); */
    /* edge_mark(elr, l); */
    /* mu_assert("Local inspect #5", strcmp(l, "ababa") == 0); */
    /* edge_mark(er, l); */
    /* mu_assert("Local inspect #6", strcmp(l, "ba") == 0); */
    /* edge_mark(erl, l); */
    /* mu_assert("Local inspect #7", strcmp(l, "ababa") == 0); */
    /* edge_mark(err, l); */
    /* mu_assert("Local inspect #8", strcmp(l, "ba") == 0); */

    /* mu_assert("Local inspect #9", el->k == -1); */
    /* mu_assert("Local inspect #10", ell->k == -1); */
    /* mu_assert("Local inspect #11", elll->k == 0); */
    /* mu_assert("Local inspect #12", ellr->k == 3); */
    /* mu_assert("Local inspect #13", elr->k == 2); */
    /* mu_assert("Local inspect #14", er->k == -1); */
    /* mu_assert("Local inspect #15", erl->k == 1); */
    /* mu_assert("Local inspect #16", err->k == 4); */

    return NULL;
}


static char *utest_stefan_kurz_example()
{
    /* STree tree, actual_tree; */
    /* char *input, *s_actual; */
    /* char s[STRING_MAX_LEN]; */
    /* s[0] = '\0'; */

    /* input = "acbcabcac"; */
    /* s_actual = "r[a[bcac4[],cbcabcac0[]],bca[bcac2[],c5[]],c[a[bcac3[],c6[]],bcabcac1[]]]"; */
    /* tree = ukkonen_naive2(input); */
    /* write2(s, tree); */
    /* read(s_actual, &actual_tree); */
    /* mu_assert("Isomorphic #1", stree_isomorphic(tree, actual_tree)); */

    return NULL;
}


char *test_vertex_ukkonen()
{
    mu_run_utest(utest_adv_alg_example);
    mu_run_utest(utest_stefan_kurz_example);
    return NULL;
}
