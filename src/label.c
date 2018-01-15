#include "label.h"


Label label_full(char *text)
{
    return label(text, 0, strlen(text));
}


Label label(const char *text, int i, int j)
{
    Label ret = malloc(sizeof(struct label));

    ret->text = text;
    ret->i = i;
    ret->j = j;

    return ret;
}


void label_mark(Label lbl, char *mark)
{
    sstring(mark, lbl->i, lbl->j - lbl->i, lbl->text);
}


void label_shrink_left(Label lbl, int k)
{
    lbl->i += k;
}


void label_set_right(Label lbl, int k)
{
    lbl->j = k;
}


char label_char_at(Label lbl, int i)
{
    if (i > lbl->j) {
        runtime_error("Index out of bounds");
    }
    return *(lbl->text + lbl->i + i);
}


void label_extend(Label lbl)
{
    lbl->j++;
}


void label_print(Label lbl)
{
    char tmp[STRING_MAX_LEN];
    label_mark(lbl, tmp);
    printf("%s\n", tmp);
}


void label_destroy(Label lbl)
{
    free(lbl);
}
