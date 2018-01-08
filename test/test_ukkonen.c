#include "test.h"
#include "ukkonen.h"
#include "reader.h"
#include "writer.h"

char *utest_ukkonen()
{
    STree t;
    char *input = "abaababa";
    char *s = malloc(sizeof(char) * STRING_INIT_LEN * 2);
    char *s_actual = "R[a[ba[ababa[],ba[]],ababa[]],ba[ababa[],ba[]]]";
    t = ukkonen_naive(input);
    write(t, s);
    mu_assert("Should equal #1", strcmp(s_actual, s) == 0);

    return NULL;
}


char *test_ukkonen()
{
    mu_run_utest(utest_ukkonen);
    return NULL;
}
