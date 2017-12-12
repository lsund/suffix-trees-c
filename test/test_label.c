#include "test.h"
#include "label.h"


char *utest_label()
{
    Label c = label_maxlen("hello", 12);
    mu_assert("Create label:", strcmp(c->mark, "hello") == 0);

    return NULL;
}

char *utest_label_extend()
{
    Label a = label_maxlen("hello", 12);
    label_extend(a, " world");
    mu_assert("Extend a label: mark", strcmp(a->mark, "hello world") == 0);
    mu_assert("Extend a label: len", a->len == 11);
    mu_assert("Extend a label: maxlen", a->max_len == 12);

    Label b = label_maxlen("hello", 12);
    label_extend(b, " maddafakka");
    mu_assert("Extend a label #2: mark", strcmp(b->mark, "hello maddafakka") == 0);
    mu_assert("Extend a label #2: len", b->len == 16);
    mu_assert("Extend a label #2: maxlen", b->max_len == 24);

    Label c = label_maxlen("hello", 6);
    label_extend_letter(c, '!');
    mu_assert("Extend a label #3: mark", strcmp(c->mark, "hello!") == 0);
    mu_assert("Extend a label #3: len", c->len == 6);
    mu_assert("Extend a label #3: maxlen", c->max_len == 6);
    label_extend_letter(c, '!');
    mu_assert("Extend a label #4: mark", strcmp(c->mark, "hello!!") == 0);
    mu_assert("Extend a label #4: len", c->len == 7);
    mu_assert("Extend a label #4: maxlen", c->max_len == 12);

    return NULL;
}


char *test_label()
{
    mu_run_utest(utest_label);
    mu_run_utest(utest_label_extend);
    return NULL;
}
