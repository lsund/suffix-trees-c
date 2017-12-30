#include "test.h"
#include "util.h"

char *utest_extend()
{
    char *buf = malloc(sizeof(char) * 128);
    strcpy(buf, "test");
    extend(buf, 'x');
    mu_assert("Extend 1:", strcmp(buf, "testx") == 0);
    extend(buf, 'x');
    mu_assert("Extend 2:", strcmp(buf, "testxx") == 0);
    return NULL;
}

char *test_util()
{
    mu_run_utest(utest_extend);
    return NULL;
}
