#include "label.h"


LabelPointer label(char *mark)
{
    LabelPointer ret = malloc(sizeof(struct label));
    size_t len       = strlen(mark);

    ret->mark        = mark;
    ret->len         = len;
    ret->i           = 0;
    ret->n           = len;

    return ret;
}


void label_shrink_left(LabelPointer lbl, int k)
{
    lbl->i += k;
}


void label_set_right(LabelPointer lbl, int k)
{
    lbl->n = k;
}


char label_char_at(LabelPointer lbl, int i)
{
    if (i > lbl->n) {
        runtime_error("Index out of bounds");
    }
    return *(lbl->mark + lbl->i + i);
}


void label_extend(LabelPointer lbl, const char c)
{
    *(lbl->mark + lbl->len) = c;
    *(lbl->mark + lbl->len + 1) = '\0';
    lbl->len++;
    lbl->n++;
}


void label_print(LabelPointer lbl)
{
    char *tmp = lbl->mark;
    tmp[lbl->n] = '\0';
    printf("%s i:%d n:%d len:%zu\n", tmp, lbl->i, lbl->n, lbl->len);
}


void label_destroy(LabelPointer lbl)
{
    free(lbl->mark);
    free(lbl);
}
