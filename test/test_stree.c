
#include "test.h"
#include "stree.h"
#include "edge.h"
#include "reader.h"
#include "writer.h"
#include "stree_permute.h"
#include "stree_compare.h"


/* char *utest_stree_split() */
/* { */
/* } */

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

char *utest_scan_prefix2()
{
    char *text = "abaabab";
    char tmp[64];
    STree2 r   = stree_init2(text);
    Vertex v1 = vertex(0, 1);   // a
    Vertex v2 = vertex(1, 3);   // ba
    Vertex v3 = vertex(3, 7);   // abab

    Vertex v4 = vertex(1, 3);   // ba
    Vertex v5 = vertex(3, 7);   // abab
    Vertex v7 = vertex(3, 7);   // abab

    Vertex v6 = vertex(5, 6);   // b
    Vertex v8 = vertex(4, 5);   // b

    stree_extend_below(r, v1);          // root -> a
    vertex_extend_below(v1, v2);        // a -> ba
    vertex_extend_below(v2, v3);        // ba -> abab
    vertex_extend_right(v1, v4);        // a -> ba
    vertex_extend_below(v4, v7);        // ba -> abab

    vertex_extend_right(v3, v6);        // abab -> b
    vertex_extend_right(v2, v5);        // ba -> abab
    vertex_extend_right(v7, v8);        // abab -> b

    TreeMatching2 tm1 = scan_prefix2(r, label2(0, 1));
    TreeMatching2 tm2 = scan_prefix2(r, label2(1, 2));
    TreeMatching2 tm3 = scan_prefix2(r, label2(0, 2));
    TreeMatching2 tm4 = scan_prefix2(r, label2(2, 6));          // aaba
    TreeMatching2 tm5 = scan_prefix2(r, label2(0, 5));          // abaab
    TreeMatching2 tm6 = scan_prefix2(r, label2(4, 7));          // bab

    mu_assert("End should exist #1", tm1.end);
    mu_assert("End should exist #2", tm2.end);
    mu_assert("End should exist #3", tm3.end);
    mu_assert("End should exist #4", tm4.end);
    mu_assert("End should exist #4", tm5.end);
    mu_assert("End should exist #4", tm6.end);

    tmp[0] = 0;
    vertex_mark(tmp, tm1.end, text);
    mu_assert("control of label #1", strcmp(tmp, "a") == 0);
    tmp[0] = 0;
    vertex_mark(tmp, tm2.end, text);
    mu_assert("control of label #2", strcmp(tmp, "ba") == 0);
    tmp[0] = 0;
    vertex_mark(tmp, tm3.end, text);
    mu_assert("control of label #3", strcmp(tmp, "ba") == 0);
    tmp[0] = 0;
    vertex_mark(tmp, tm4.end, text);
    mu_assert("control of label #3", strcmp(tmp, "abab") == 0);
    tmp[0] = 0;
    vertex_mark(tmp, tm5.end, text);
    mu_assert("control of label #3", strcmp(tmp, "abab") == 0);
    tmp[0] = 0;
    vertex_mark(tmp, tm6.end, text);
    mu_assert("control of label #3", strcmp(tmp, "b") == 0);

    return NULL;
}

char *test_stree()
{
    mu_run_utest(utest_scan_prefix);
    mu_run_utest(utest_scan_prefix2);
    mu_run_utest(utest_stree_sibling_with);
    return NULL;
}
