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
    char *buf = malloc(sizeof(char) * STRING_INIT_LEN);
    sprintf(buf, "%s", "hello");
    Label c = label_maxlen(buf, 6);
    label_extend(c, '!');
    mu_assert("Extend a label #3: mark", strcmp(c->mark, "hello!") == 0);
    mu_assert("Extend a label #3: len", c->len == 6);
    label_extend(c, '!');
    mu_assert("Extend a label #4: mark", strcmp(c->mark, "hello!!") == 0);
    mu_assert("Extend a label #4: len", c->len == 7);

    return NULL;
}


char *test_label()
{
    mu_run_utest(utest_label);
    mu_run_utest(utest_label_extend);
    return NULL;
}
