#include "test.h"
#include "util.h"

char *utest_factorial()
{
    mu_assert("Factorial #1", factorial(5) == 120);
    mu_assert("Factorial #2", factorial(7) == 5040);
    return NULL;
}

char *test_util()
{
    mu_run_utest(utest_factorial);
    return NULL;
}
