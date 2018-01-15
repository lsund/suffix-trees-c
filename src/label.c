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


void label_mark(Label l, char *mark)
{
    sstring(mark, l->i, l->j - l->i, l->text);
}


void label_shrink_left(Label l, int k)
{
    l->i += k;
}


void label_set_right(Label l, int k)
{
    l->j = k;
}


char label_char_at(Label l, int i)
{
    if (i > l->j) {
        runtime_error("Index out of bounds");
    }
    return *(l->text + l->i + i);
}


void label_extend(Label l)
{
    l->j++;
}


void label_print(Label l)
{
    char tmp[STRING_MAX_LEN];
    label_mark(l, tmp);
    printf("%s\n", tmp);
}


void label_destroy(Label l)
{
    free(l);
}
