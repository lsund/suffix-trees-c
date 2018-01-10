#include "test.h"
#include "label.h"


char *utest_label_shrink_left()
{
    LabelPointer lbl = label("hello world", 0, 5);

    char tmp[64];

    label_shrink_left(lbl, 2);
    label_mark(lbl, tmp);
    mu_assert("Shrink left #1", strcmp(tmp, "llo") == 0);

    label_shrink_left(lbl, 2);
    label_mark(lbl, tmp);
    mu_assert("Shrink left #2", strcmp(tmp, "o") == 0);

    return NULL;
}


char *utest_label_set_right()
{
    LabelPointer lbl = label("hello world", 0, 5);

    char tmp[64];

    label_set_right(lbl, 10);
    label_mark(lbl, tmp);
    mu_assert("Set right #1", strcmp(tmp, "hello worl") == 0);

    label_set_right(lbl, 2);
    label_mark(lbl, tmp);
    mu_assert("Set right #2", strcmp(tmp, "he") == 0);

    return NULL;
}


char *utest_label_char_at()
{
    LabelPointer lbl = label("hello world", 1, 10);

    mu_assert("Char at #1", label_char_at(lbl, 0) == 'e');
    mu_assert("Char at #1", label_char_at(lbl, 3) == 'o');

    return NULL;
}


char *utest_label_extend()
{
    LabelPointer lbl = label("hello world", 1, 5);
    char tmp[64];

    label_mark(lbl, tmp);
    mu_assert("Extend #1", strcmp(tmp, "ello") == 0);
    label_extend(lbl);
    label_mark(lbl, tmp);
    mu_assert("Extend #1", strcmp(tmp, "ello ") == 0);
    label_extend(lbl);
    label_mark(lbl, tmp);
    mu_assert("Extend #1", strcmp(tmp, "ello w") == 0);

    return NULL;
}


char *utest_label()
{
    LabelPointer c = label_full("hello");
    mu_assert("Create label:", strcmp(c->text, "hello") == 0);

    return NULL;
}

char *test_label()
{
    mu_run_utest(utest_label);
    mu_run_utest(utest_label_shrink_left);
    mu_run_utest(utest_label_set_right);
    mu_run_utest(utest_label_char_at);
    mu_run_utest(utest_label_extend);
    return NULL;
}
