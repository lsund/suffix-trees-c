#include "label.h"


Label2 label2(int i, int j)
{
    Label2 ret = malloc(sizeof(struct label));
    ret->i = i;
    ret->j = j;
    return ret;

}

void label_mark2(char *t, const Label2 l, const char *x)
{
    if (l->i < 0 || l->j > (int) strlen(x)) {
        printf("%d %d\n", l->i, l->j);
        runtime_error("Index out of bounds");
    }
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

int label_equals(const char *x, Label2 l1, Label2 l2)
{
    if (label_is_undefined(l1) && label_is_undefined(l2)) {
        return 1;
    }
    char tmp1[STRING_MAX_LEN];
    char tmp2[STRING_MAX_LEN];
    label_mark2(tmp1, l1, x);
    label_mark2(tmp2, l2, x);
    return strcmp(tmp1, tmp2) == 0;
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
