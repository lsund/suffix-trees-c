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


void label_extend(LabelPointer lbl, const char c)
{
    char *new = malloc(sizeof(char) * (lbl->len + 3));
    sprintf(new, "%s%c", lbl->mark, c);
    free(lbl->mark);
    lbl->mark = new;
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
