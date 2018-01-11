#include "test.h"
#include "ukkonen.h"
#include "reader.h"
#include "writer.h"

char *utest_ukkonen()
{
    STree tree;
    char *input, *s_actual, *s_actual2;
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
    mu_assert("Should equal #3", strcmp(s_actual, s) == 0);

    s[0] = '\0';
    input = "abaa";
    s_actual = "R[a[baa0[],a2[]],baa1[]]";
    tree = ukkonen_naive(input);
    write(tree, s);
    /* printf("res: %s\n1:   %s\n", s, s_actual); */
    mu_assert("Should equal #4", strcmp(s_actual, s) == 0);

    s[0] = '\0';
    input = "abaab";
    s_actual = "R[a[baab0[],ab2[]],baab1[]]";
    tree = ukkonen_naive(input);
    write(tree, s);
    /* printf("res: %s\n1:   %s\n", s, s_actual); */
    mu_assert("Should equal #5", strcmp(s_actual, s) == 0);

    s[0] = '\0';
    input = "abaaba";
    s_actual = "R[a[baaba0[],aba2[]],baaba1[]]";
    tree = ukkonen_naive(input);
    write(tree, s);
    mu_assert("Should equal #6", strcmp(s_actual, s) == 0);

    s[0] = '\0';
    input = "abaabab";
    s_actual = "R[a[ba[abab0[],b3[]],abab2[]],ba[abab1[],b4[]]]";
    s_actual2 = "R[a[ba[abab0[],b3[]],abab2[]],ba[b4[],abab1[]]]";
    tree = ukkonen_naive(input);
    write(tree, s);
    /* printf("res: %s\n1:   %s\n2:   %s\n", s, s_actual, s_actual2); */
    int pass = strcmp(s_actual, s) == 0 || strcmp(s_actual2, s) == 0;
    mu_assert("Should equal #7", pass);

    s[0] = '\0';
    input = "abaababa";
    s_actual = "R[a[ba[ababa0[],ba3[]],ababa2[]],ba[ababa1[],ba4[]]]";
    s_actual2 = "R[a[ba[ababa0[],ba3[]],ababa2[]],ba[ba4[],ababa1[]]]";
    tree = ukkonen_naive(input);
    write(tree, s);
    /* printf("res: %s\n1:   %s\n2:   %s\n", s, s_actual, s_actual2); */
    pass = strcmp(s_actual, s) == 0 || strcmp(s_actual2, s) == 0;
    mu_assert("Should equal #7", pass);

    return NULL;
}


char *test_ukkonen()
{
    mu_run_utest(utest_ukkonen);
    return NULL;
}
