#include "test.h"
#include "reader.h"
#include "writer.h"


char *utest_read2()
{
    STree2 tree;
    char *s;
    char *text = "abaababa";

    char t[STRING_MAX_LEN];
    t[0] = '\0';
    s = "r[<0,1,0>[]]";
    tree = stree_init2(s);
    read2(s, tree);
    write2(t, tree);
    mu_assert("Should equal #0", strcmp(s, t) == 0);

    t[0] = '\0';
    s = "r[<0,2,0>[],<1,2,1>[]]";
    tree = stree_init2(s);
    read2(s, tree);
    write2(t, tree);
    mu_assert("Should equal #2", strcmp(s, t) == 0);

    t[0] = '\0';
    s = "r[<0,3,0>[],<0,2,1>[]]";
    tree = stree_init2(s);
    read2(s, tree);
    write2(t, tree);
    mu_assert("Should equal #1", strcmp(s, t) == 0);

    t[0] = '\0';
    s = "r[<0,1,-1>[<1,4,0>[],<0,1,2>[]],<1,4,1>[]]";
    tree = stree_init2(s);
    read2(s, tree);
    write2(t, tree);
    mu_assert("Should equal #3", strcmp(s, t) == 0);

    t[0] = '\0';
    s = "r[<0,1,-1>[<1,5,0>[],<0,2,2>[]],<1,5,1>[]]";
    tree = stree_init2(s);
    read2(s, tree);
    write2(t, tree);
    mu_assert("Should equal #4", strcmp(s, t) == 0);

    t[0] = '\0';
    s = "r[<0,1,-1>[<1,3,-1>[<3,7,0>[],<1,2,3>[]],<3,7,2>[]],<1,3,-1>[<1,2,4>[],<3,7,2>[]]]";
    tree = stree_init2(s);
    read2(s, tree);
    write2(t, tree);
    mu_assert("Should equal #6", strcmp(s, t) == 0);

    text = "abcdx";
    char tmp[64];
    char *rep10 = "r[<0,1,1>[<2,3,3>[],<3,4,4>[]],<1,2,2>[]]";
    char *rep11 = "r[<1,2,2>[],<0,1,1>[<3,4,4>[],<2,3,3>[]]]";
    char *rep12 = "r[<1,2,-1>[],<0,1,-1>[<3,4,-1>[],<2,3,3>[]]]";

    STree2 t10 = stree_init2(text);
    STree2 t11 = stree_init2(text);
    STree2 t12 = stree_init2(text);
    read2(rep10, t10);
    read2(rep11, t11);
    read2(rep12, t12);
    Vertex r10 = t10->r;
    Vertex r11 = t11->r;
    Vertex r12 = t12->r;

    label_mark2(tmp, r10->c->l, text);
    mu_assert("Should equal #7", strcmp(tmp, "a") == 0);
    label_mark2(tmp, r10->c->s->l, text);
    mu_assert("Should equal #8", strcmp(tmp, "b") == 0);
    label_mark2(tmp, r10->c->c->l, text);
    mu_assert("Should equal #8", strcmp(tmp, "c") == 0);
    label_mark2(tmp, r10->c->c->s->l, text);
    mu_assert("Should equal #8", strcmp(tmp, "d") == 0);

    label_mark2(tmp, r11->c->l, text);
    mu_assert("Should equal #7", strcmp(tmp, "b") == 0);
    label_mark2(tmp, r11->c->s->l, text);
    mu_assert("Should equal #8", strcmp(tmp, "a") == 0);
    label_mark2(tmp, r11->c->s->c->l, text);
    mu_assert("Should equal #8", strcmp(tmp, "d") == 0);
    label_mark2(tmp, r11->c->s->c->s->l, text);
    mu_assert("Should equal #8", strcmp(tmp, "c") == 0);

    label_mark2(tmp, r12->c->l, text);
    mu_assert("Should equal #7", strcmp(tmp, "b") == 0);
    label_mark2(tmp, r12->c->s->l, text);
    mu_assert("Should equal #8", strcmp(tmp, "a") == 0);
    label_mark2(tmp, r12->c->s->c->l, text);
    mu_assert("Should equal #8", strcmp(tmp, "d") == 0);
    label_mark2(tmp, r12->c->s->c->s->l, text);
    mu_assert("Should equal #8", strcmp(tmp, "c") == 0);

    return NULL;
}

char *test_reader()
{
    mu_run_utest(utest_read2);

    return NULL;
}

