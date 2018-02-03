#include "test.h"
#include "reader.h"
#include "writer.h"

char *utest_read()
{
    STree tree;
    char *s;

    char t[STRING_MAX_LEN];
    t[0] = '\0';
    s = "root[a[c3[],d4[]],b2[]]";
    read(s, &tree);
    write(t, tree);
    mu_assert("Should equal #0", strcmp(s, t) == 0);

    t[0] = '\0';
    s = "root[a[a1[],c[x2[],y3[]]]]";
    read(s, &tree);
    write(t, tree);
    mu_assert("Should equal #1", strcmp(s, t) == 0);

    t[0] = '\0';
    s = "root[a[b1[],c[d2[],e3[]]]]";
    read(s, &tree);
    write(t, tree);
    mu_assert("Should equal #2", strcmp(s, t) == 0);

    t[0] = '\0';
    s = "root[a[b1[],c3[],d2[]]]";
    read(s, &tree);
    write(t, tree);
    mu_assert("Should equal #3", strcmp(s, t) == 0);

    t[0] = '\0';
    s = "root[a1[],x2[],c3[]]";
    read(s, &tree);
    write(t, tree);
    mu_assert("Should equal #4", strcmp(s, t) == 0);

    t[0] = '\0';
    s = "root1[]";
    read(s, &tree);
    write(t, tree);
    mu_assert("Should equal #5", strcmp(s, t) == 0);

    t[0] = '\0';
    s = "r[b1[]]";
    read(s, &tree);
    write(t, tree);
    mu_assert("Should equal #6", strcmp(s, t) == 0);

    t[0] = '\0';
    s = "root[b1[],c2[]]";
    read(s, &tree);
    write(t, tree);
    mu_assert("Should equal #7", strcmp(s, t) == 0);

    t[0] = '\0';
    s = "root[b[c[d1[]]]]";
    read(s, &tree);
    write(t, tree);
    mu_assert("Should equal #8", strcmp(s, t) == 0);

    t[0] = '\0';
    s = "root[a1[],b2[]]";
    read(s, &tree);
    write(t, tree);
    mu_assert("Should equal #8", strcmp(s, t) == 0);

    t[0] = '\0';
    s = "R[a[b[c0[],d3[]],e2[]],f[g1[],h4[]]]";
    read(s, &tree);
    write(t, tree);
    mu_assert("Should equal #9", strcmp(s, t) == 0);

    t[0] = '\0';
    s = "R[a[ba[abab0[],b3[]],abab2[]],ba[b4[],abab1[]]]";
    read(s, &tree);
    write(t, tree);
    mu_assert("Should equal #10", strcmp(s, t) == 0);

    return NULL;
}

char *utest_read2()
{
    STree2 tree;
    char *s;
    char *text = "abaababa";

    char t[STRING_MAX_LEN];
    t[0] = '\0';
    s = "r[<0,1,0>[]]";
    tree = stree_init2(s);
    read2(text, s, tree);
    write2(t, tree);
    mu_assert("Should equal #0", strcmp(s, t) == 0);

    t[0] = '\0';
    s = "r[<0,2,0>[],<1,2,1>[]]";
    tree = stree_init2(s);
    read2(text, s, tree);
    write2(t, tree);
    mu_assert("Should equal #2", strcmp(s, t) == 0);

    t[0] = '\0';
    s = "r[<0,3,0>[],<0,2,1>[]]";
    tree = stree_init2(s);
    read2(text, s, tree);
    write2(t, tree);
    mu_assert("Should equal #1", strcmp(s, t) == 0);

    t[0] = '\0';
    s = "r[<0,1,-1>[<1,4,0>[],<0,1,2>[]],<1,4,1>[]]";
    tree = stree_init2(s);
    read2(text, s, tree);
    write2(t, tree);
    mu_assert("Should equal #3", strcmp(s, t) == 0);

    t[0] = '\0';
    s = "r[<0,1,-1>[<1,5,0>[],<0,2,2>[]],<1,5,1>[]]";
    tree = stree_init2(s);
    read2(text, s, tree);
    write2(t, tree);
    mu_assert("Should equal #4", strcmp(s, t) == 0);

    t[0] = '\0';
    s = "r[<0,1,-1>[<1,3,-1>[<3,7,0>[],<1,2,3>[]],<3,7,2>[]],<1,3,-1>[<1,2,4>[],<3,7,2>[]]]";
    tree = stree_init2(s);
    read2(text, s, tree);
    write2(t, tree);
    mu_assert("Should equal #6", strcmp(s, t) == 0);

    return NULL;
}

char *test_reader()
{
    mu_run_utest(utest_read);
    mu_run_utest(utest_read2);

    return NULL;
}

