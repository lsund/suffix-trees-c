#include "label.h"


Label label_maxlen(char *mark, size_t maxlen)
{
    Label ret = malloc(sizeof(struct label));
    ret->mark = mark;
    ret->len  = 0;

    if (strlen(mark) > maxlen) {
        runtime_error("Length of mark exceeds maxlen");
    }

    ret->len = strlen(mark);

    return ret;
}


Label label(char *mark)
{
    return label_maxlen(mark, STRING_INIT_LEN);
}


void label_extend(Label lbl, const char c)
{
    char *new = malloc(sizeof(char) * (lbl->len + 3));
    sprintf(new, "%s%c", lbl->mark, c);
    free(lbl->mark);
    lbl->mark = new;
    lbl->len++;
}


void label_destroy(Label lbl)
{
    free(lbl->mark);
    free(lbl);
}
