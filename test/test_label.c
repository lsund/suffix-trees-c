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
