#include "test.h"
#include "ukkonen.h"
#include "reader.h"
#include "writer.h"

char *utest_ukkonen()
{
    STree tree;
    char *input, *s_actual;
    char s[STRING_INIT_LEN];
    s[0] = '\0';

    input = "a";
    s_actual = "R[a0[]]";
    tree = ukkonen_naive(input);
    write(tree, s);
    mu_assert("Should equal #1", strcmp(s_actual, s) == 0);

    s[0] = '\0';
    input = "ab";
    s_actual = "R[ab0[],b1[]]";
    tree = ukkonen_naive(input);
    write(tree, s);
    mu_assert("Should equal #2", strcmp(s_actual, s) == 0);

    s[0] = '\0';
    input = "aba";
    s_actual = "R[aba0[],ba1[]]";
    tree = ukkonen_naive(input);
    write(tree, s);
    mu_assert("Should equal #2", strcmp(s_actual, s) == 0);

    s[0] = '\0';
    input = "abaa";
    s_actual = "R[a[baa0[],a2[]],baa1[]]";
    tree = ukkonen_naive(input);
    write(tree, s);
    printf("%s\n%s\n%zu\n%zu\n", s, s_actual, strlen(s), strlen(s_actual));
    mu_assert("Should equal #2", strcmp(s_actual, s) == 0);

    /* input = "abaababa"; */
    /* s_actual = "R[a[ba[ababa[],ba[]],ababa[]],ba[ababa[],ba[]]]"; */
    /* t = ukkonen_naive(input); */
    /* write(tree, s); */
    /* mu_assert("Should equal #1", strcmp(s_actual, s) == 0); */
    /* free(s); */

    return NULL;
}


char *test_ukkonen()
{
    mu_run_utest(utest_ukkonen);
    return NULL;
}
