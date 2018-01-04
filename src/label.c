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


char label_char_at(LabelPointer lbl, int i)
{
    if (i > lbl->n) {
        /* printf("%s %d %d\n", lbl->mark, i, lbl->n); */
        runtime_error("Index out of bounds");
    }
    return *(lbl->mark + lbl->i + i);
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


/* void label_string(LabelPointer lbl) */
/* { */
/* } */


void label_destroy(LabelPointer lbl)
{
    free(lbl->mark);
    free(lbl);
}
