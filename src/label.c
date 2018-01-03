#include "label.h"


LabelPointer label(char *mark)
{
    LabelPointer ret = malloc(sizeof(struct label));
    ret->mark        = mark;
    ret->len         = strlen(mark);
    ret->i           = 0;

    return ret;
}


void label_extend(LabelPointer lbl, const char c)
{
    char *new = malloc(sizeof(char) * (lbl->len + 3));
    sprintf(new, "%s%c", lbl->mark, c);
    free(lbl->mark);
    lbl->mark = new;
    lbl->len++;
}


void label_destroy(LabelPointer lbl)
{
    free(lbl->mark);
    free(lbl);
}
