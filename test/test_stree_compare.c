#include "test.h"
#include "stree.h"
#include "stree_compare.h"
#include "reader.h"
#include "writer.h"

static int symmetric_isomorphic2(STree2 t1, STree2 t2)
{
    return stree_isomorphic2(t1, t2) && stree_isomorphic2(t2, t1);
}

char *utest_stree_equals2()
{
    char *text ="abc";
    STree2 t1, t2, t3, t4;

    char *s1, *s2, *s3, *s4;
    s1 = "r[<0,1,1>[],<1,2,2>[]]";
    s2 = "r[<1,2,1>[],<0,1,2>[]]";
    s3 = "r[<1,2,1>[]]";
    s4 = "r[<1,2,1>[],<0,1,2>[<2,3,0>[]]";

    char tmp[STRING_MAX_LEN];
    t1 = stree_init2(text);
    t2 = stree_init2(text);
    t3 = stree_init2(text);
    t4 = stree_init2(text);

    read2(s1, t1);
    read2(s2, t2);

    mu_assert("Equals #1", !stree_equals2(t1, t2));
    mu_assert("Equals #2", stree_equals2(t1, t1));
    mu_assert("Equals #3", stree_equals2(t2, t2));
    mu_assert("Equals #4", !stree_equals2(t2, t1));
    read2(s1, t2);
    mu_assert("Equals #5", stree_equals2(t1, t2));
    read2(s2, t2);
    read2(s3, t3);

    write2(tmp, t3);
    write2(tmp, t2);
    mu_assert("Equals #6", !stree_equals2(t2, t3));

    read2(s4, t4);
    mu_assert("Equals #7", !stree_equals2(t2, t4));

    return NULL;
}

char *utest_stree_isomorphic2()
{
    char *text = "abcdx";
    /* char tmp[75]; */

    // These are isomorphic
    char *rep1 = "r[<0,1,1>[],<1,2,2>[]]";
    char *rep2 = "r[<1,2,2>[],<0,1,1>[]]";
    char *rep3 = "r[<1,2,3>[],<0,1,6>[]]";

    // This is not
    char *rep4 = "r[<1,2,3>[],<0,2,6>[]]";

    STree2 t1 = stree_init2(text);
    STree2 t2 = stree_init2(text);
    STree2 t3 = stree_init2(text);
    STree2 t4 = stree_init2(text);
    STree2 t5 = stree_init2(text);
    STree2 t6 = stree_init2(text);
    STree2 t7 = stree_init2(text);
    STree2 t8 = stree_init2(text);
    STree2 t9 = stree_init2(text);
    STree2 t10 = stree_init2(text);
    STree2 t11 = stree_init2(text);
    STree2 t12 = stree_init2(text);
    STree2 t13 = stree_init2(text);

    // These are isomorphic
    char *rep5 = "r[<1,2,1>[],<0,1,2>[],<2,3,3>[]]";
    char *rep6 = "r[<0,1,1>[],<2,3,2>[],<1,2,3>[]]";
    char *rep7 = "r[<2,3,1>[],<1,2,2>[],<0,1,3>[]]";
    char *rep8 = "r[<2,3,1>[],<0,1,2>[],<1,2,3>[]]";

    // This is not
    char *rep9 = "r[<2,3,1>[],<2,3,2>[],<1,2,3>[]]";

    // Depth 2
    // These are isomorphic
    char *rep10 = "r[<0,1,1>[<2,3,3>[],<3,4,4>[]],<1,2,2>[]]";
    char *rep11 = "r[<1,2,2>[],<0,1,1>[<3,4,4>[],<2,3,3>[]]]";
    char *rep12 = "r[<0,1,1>[<3,4,4>[],<2,3,3>[]],<1,2,2>[]]";

    // This is not
    char *rep13 = "r[<0,1,1>[<4,5,4>[],<2,3,3>[]],<1,2,2>[]]";


    read2(rep1, t1);
    read2(rep2, t2);
    read2(rep3, t3);
    read2(rep4, t4);
    read2(rep5, t5);
    read2(rep6, t6);
    read2(rep7, t7);
    read2(rep8, t8);
    read2(rep9, t9);
    read2(rep10, t10);
    read2(rep11, t11);
    read2(rep12, t12);
    read2(rep13, t13);

    mu_assert("Isomorphic #0", stree_isomorphic2(t1, t1));
    mu_assert("Isomorphic #1", stree_isomorphic2(t1, t2));
    mu_assert("Isomorphic #1", stree_isomorphic2(t1, t2));
    mu_assert("Isomorphic #1", stree_isomorphic2(t1, t2));
    mu_assert("Isomorphic #1", stree_isomorphic2(t1, t2));
    mu_assert("Isomorphic #2", symmetric_isomorphic2(t1, t2));
    mu_assert("Isomorphic #3", symmetric_isomorphic2(t2, t2));
    mu_assert("Isomorphic #5", symmetric_isomorphic2(t1, t3));
    mu_assert("Isomorphic #6", !stree_isomorphic2(t1, t4));

    mu_assert("Isomorphic #7", symmetric_isomorphic2(t5, t6));
    mu_assert("Isomorphic #9", symmetric_isomorphic2(t5, t7));
    mu_assert("Isomorphic #10", symmetric_isomorphic2(t5, t8));
    mu_assert("Isomorphic #11", symmetric_isomorphic2(t6, t7));
    mu_assert("Isomorphic #12", symmetric_isomorphic2(t6, t8));
    mu_assert("Isomorphic #13", symmetric_isomorphic2(t7, t8));
    mu_assert("Isomorphic #14", !stree_isomorphic2(t8, t9));
    mu_assert("Isomorphic #15", !stree_isomorphic2(t5, t9));
    mu_assert("Isomorphic #16", !stree_isomorphic2(t9, t6));

    mu_assert("Isomorphic #17", symmetric_isomorphic2(t10, t11));
    mu_assert("Isomorphic #18", symmetric_isomorphic2(t10, t12));
    mu_assert("Isomorphic #19", !stree_isomorphic2(t10, t13));

    char *rep14 = "r[<0,1,-1>[<1,3,-1>[<3,8,0>[],<6,8,3>[]],<3,8,2>[]],<1,3,-1>[<3,8,1>[],<6,8,4>[]]]";
    text = "abaababa";
    STree2 t14 = stree_init2(text);
    read2(rep14, t14);
    mu_assert("Should be isomorphic #20", stree_isomorphic2(t14, t14));

    return NULL;
}


char *test_stree_compare()
{
    mu_run_utest(utest_stree_equals2);
    mu_run_utest(utest_stree_isomorphic2);
    return NULL;
}
