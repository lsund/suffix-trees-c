#include "label.h"

///////////////////////////////////////////////////////////////////////////////
// new


Label2 label2(int i, int j)
{
    Label2 ret = malloc(sizeof(struct label));
    ret->i = i;
    ret->j = j;
    return ret;

}

void label_mark2(char *t, const Label2 l, const char *x)
{
    sstring(t, l->i, l->j - l->i, x);
}


char label_char_at_2(const char *x, const Label2 lbl, const int i)
{
    if (i > lbl->i) {
        return '\0';
    } else {
        return *(x + lbl->i + i);
    }
}

void label_shrink_left2(const Label2 lbl, const int n)
{
    lbl->i += n;
}


void label_extend_right2(const Label2 lbl)
{
    lbl->j++;
}


void label_set_right2(const Label2 l, const int i)
{
    l->j = i;
}


int label_is_undefined(const Label2 l)
{
    return l->i == -1 && l->j == -1;
}

void label_print2(const char *x, Label2 l)
{
    char tmp[STRING_MAX_LEN];
    label_mark2(tmp, l, x);
    printf("%s\n", tmp);
}

///////////////////////////////////////////////////////////////////////////////
// old


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
