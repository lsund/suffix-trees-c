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


char *test_reader()
{
    mu_run_utest(utest_read);

    return NULL;
}

