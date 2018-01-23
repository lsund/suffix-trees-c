#include "test.h"
#include "util.h"

char *utest_factorial()
{
    mu_assert("Factorial #1", factorial(5) == 120);
    mu_assert("Factorial #2", factorial(7) == 5040);
    return NULL;
}

char *utest_nth_permutation()
{
    char tmp[500];
    char seq[500];
    seq[0] = 0;
    strcat(seq, "012");
    nth_permutation(tmp, 0, seq);
    mu_assert("Permutation #1", strcmp(tmp, "012") == 0);
    nth_permutation(tmp, 1, seq);
    mu_assert("Permutation #2", strcmp(tmp, "021") == 0);
    nth_permutation(tmp, 2, seq);
    mu_assert("Permutation #3", strcmp(tmp, "102") == 0);
    nth_permutation(tmp, 3, seq);
    mu_assert("Permutation #4", strcmp(tmp, "120") == 0);
    nth_permutation(tmp, 4, seq);
    mu_assert("Permutation #5", strcmp(tmp, "210") == 0);
    nth_permutation(tmp, 5, seq);
    mu_assert("Permutation #6", strcmp(tmp, "201") == 0);

    return NULL;
}

char *utest_nth_permutation_inverse()
{
    mu_assert("Permutation inverse #1", permutation_inverse_number(0, 3) == 0);
    mu_assert("Permutation inverse #2", permutation_inverse_number(1, 3) == 1);
    mu_assert("Permutation inverse #3", permutation_inverse_number(2, 3) == 2);
    mu_assert("Permutation inverse #4", permutation_inverse_number(3, 3) == 5);
    mu_assert("Permutation inverse #5", permutation_inverse_number(4, 3) == 4);
    mu_assert("Permutation inverse #6", permutation_inverse_number(5, 3) == 3);

    return NULL;
}

char *test_util()
{
    mu_run_utest(utest_factorial);
    mu_run_utest(utest_nth_permutation);
    mu_run_utest(utest_nth_permutation_inverse);
    return NULL;
}

