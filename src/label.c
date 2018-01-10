#include "label.h"


LabelPointer label_full(char *text)
{
    return label(text, 0, strlen(text));
}


LabelPointer label(const char *text, int i, int j)
{
    LabelPointer ret = malloc(sizeof(struct label));

    ret->text = text;
    ret->i = i;
    ret->j = j;

    return ret;
}


/* LabelPointer label(char *mark) */
/* { */
/*     LabelPointer ret = malloc(sizeof(struct label)); */
/*     size_t len       = strlen(mark); */

/*     ret->mark        = mark; */
/*     ret->len         = len; */
/*     ret->i           = 0; */
/*     ret->j           = len; */

/*     return ret; */
/* } */


void label_mark(LabelPointer lbl, char *mark)
{
    sstring(mark, lbl->i, lbl->j - lbl->i, lbl->text);
}


void label_shrink_left(LabelPointer lbl, int k)
{
    lbl->i += k;
}


void label_set_right(LabelPointer lbl, int k)
{
    lbl->j = k;
}


char label_char_at(LabelPointer lbl, int i)
{
    if (i > lbl->j) {
        runtime_error("Index out of bounds");
    }
    return *(lbl->text + lbl->i + i);
}


void label_extend(LabelPointer lbl)
{
    lbl->j++;
}


void label_print(LabelPointer lbl)
{
    const char *tmp = lbl->text;
    printf ("%.*s\n", lbl->j - lbl->i, tmp + lbl->i);
}


void label_destroy(LabelPointer lbl)
{
    free(lbl);
}
