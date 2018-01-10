#include "label.h"


LabelPointer label2(const char *text, int i, int j)
{
    LabelPointer ret = malloc(sizeof(struct label));
    ret->text = text;
    ret->i = i;
    ret->j = j;
    return ret;
}


LabelPointer label(char *mark)
{
    LabelPointer ret = malloc(sizeof(struct label));
    size_t len       = strlen(mark);

    ret->mark        = mark;
    ret->len         = len;
    ret->i           = 0;
    ret->j           = len;

    return ret;
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
    return *(lbl->mark + lbl->i + i);
}


void label_extend(LabelPointer lbl, const char c)
{
    *(lbl->mark + lbl->len) = c;
    *(lbl->mark + lbl->len + 1) = '\0';
    lbl->len++;
    lbl->j++;
}


void label_print(LabelPointer lbl)
{
    char *tmp = lbl->mark;
    tmp[lbl->j] = '\0';
    printf("%s i:%d n:%d len:%zu\n", tmp, lbl->i, lbl->j, lbl->len);
}
void label_print2(LabelPointer lbl)
{
    const char *tmp = lbl->text;
    printf ("%.*s\n", lbl->j - lbl->i, tmp + lbl->i);
}


void label_destroy(LabelPointer lbl)
{
    free(lbl->mark);
    free(lbl);
}
