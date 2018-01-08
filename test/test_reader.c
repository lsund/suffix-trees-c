#include "test.h"
#include "reader.h"
#include "writer.h"

char *utest_read()
{
    STree tree;
    char *s, *t;

    t = malloc(sizeof(char) * STRING_INIT_LEN);
    s = "root[a[ba[],c[x[],y[]]]]";
    read(s, &tree);
    write(tree, t);
    mu_assert("Should equal", strcmp(s, t) == 0);


    free(t);
    t = malloc(sizeof(char) * STRING_INIT_LEN);
    s = "root[]";
    read(s, &tree);
    write(tree, t);
    mu_assert("Should equal", strcmp(s, t) == 0);


    free(t);
    t = malloc(sizeof(char) * STRING_INIT_LEN);
    s = "root[b[],c[],d[]]";
    read(s, &tree);
    write(tree, t);
    mu_assert("Should equal", strcmp(s, t) == 0);

    free(t);
    t = malloc(sizeof(char) * STRING_INIT_LEN);
    s = "root[b[c[d[]]]]";
    read(s, &tree);
    write(tree, t);
    mu_assert("Should equal", strcmp(s, t) == 0);

    return NULL;
}

char *test_reader()
{
    mu_run_utest(utest_read);

    return NULL;
}

