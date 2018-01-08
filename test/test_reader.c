#include "test.h"
#include "reader.h"
#include "writer.h"

char *utest_read()
{
    STree tree;
    char *s, *t;

    t = malloc(sizeof(char) * STRING_INIT_LEN);
    s = "root[a[a[1],c[x[2],y[3]]]]";
    read(s, &tree);
    write(tree, t);
    mu_assert("Should equal", strcmp(s, t) == 0);
    free(t);

    t = malloc(sizeof(char) * STRING_INIT_LEN);
    s = "root[a[b[1],c[d[2],e[3]]]]";
    read(s, &tree);
    write(tree, t);
    mu_assert("Should equal", strcmp(s, t) == 0);
    free(t);

    t = malloc(sizeof(char) * STRING_INIT_LEN);
    s = "root[a[b[1],c[1],d[2]]]";
    read(s, &tree);
    write(tree, t);
    mu_assert("Should equal", strcmp(s, t) == 0);
    free(t);

    t = malloc(sizeof(char) * STRING_INIT_LEN);
    s = "root[a[1],x[2],c[3]]";
    read(s, &tree);
    write(tree, t);
    mu_assert("Should equal", strcmp(s, t) == 0);
    free(t);

    t = malloc(sizeof(char) * STRING_INIT_LEN);
    s = "root[1]";
    read(s, &tree);
    write(tree, t);
    mu_assert("Should equal #1", strcmp(s, t) == 0);
    free(t);

    t = malloc(sizeof(char) * STRING_INIT_LEN);
    s = "root[b[1]]";
    read(s, &tree);
    write(tree, t);
    mu_assert("Should equal #1", strcmp(s, t) == 0);
    free(t);

    t = malloc(sizeof(char) * STRING_INIT_LEN);
    s = "root[b[1],c[2]]";
    read(s, &tree);
    write(tree, t);
    mu_assert("Should equal", strcmp(s, t) == 0);
    free(t);

    t = malloc(sizeof(char) * STRING_INIT_LEN);
    s = "root[b[c[d[1]]]]";
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

