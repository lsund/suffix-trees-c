#include "label.h"


Label label_full(char *s)
{
    return label(s, 0, strlen(s));
}


Label label(const char *s, const int i, const int j)
{
    Label l = malloc(sizeof(struct label));

    l->s = s;
    l->i = i;
    l->j = j;

    return l;
}

void label_mark(Label l, char *t)
{
    sstring(t, l->i, l->j - l->i, l->s);
}


void label_shrink_left(Label l, const int n)
{
    l->i += n;
}


void label_set_right(Label l, const int i)
{
    l->j = i;
}


char label_char_at(Label l, const int i)
{
    if (i > l->j) {
        return 0;
    } else {
        return *(l->s + l->i + i);
    }
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
