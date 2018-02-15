
#include "test.h"
#include "stree.h"
#include "reader.h"
#include "writer.h"
#include "stree_permute.h"
#include "stree_compare.h"



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
    mu_run_utest(utest_scan_prefix2);
    return NULL;
}
