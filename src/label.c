#include "label.h"


Label label_maxlen(const char *mark, size_t maxlen)
{
    Label ret = malloc(sizeof(struct label));
    ret->mark    = NULL;
    ret->len     = 0;
    ret->max_len = 0;

    if (strlen(mark) > maxlen) {
        return ret;
    }

    ret->mark = malloc(sizeof(char) * maxlen);
    sprintf(ret->mark, "%s", mark);
    ret->len = strlen(mark);
    ret->max_len = maxlen;

    return ret;
}


Label label(const char *mark)
{
    return label_maxlen(mark, STRING_INIT_LEN);
}


void label_extend(Label lbl, const char c)
{

    if (lbl->len + 1 > lbl->max_len) {
        char tmp[lbl->len];
        sprintf(tmp, "%s", lbl->mark);

        free(lbl->mark);
        lbl->max_len *= 2;
        lbl->mark    = NULL;
        lbl->mark    = malloc(sizeof(char) * lbl->max_len * 2);

        sprintf(lbl->mark, "%s%c", tmp, c);
    }

    sprintf(lbl->mark, "%s%c", lbl->mark, c);
    lbl->len++;
}


void label_destroy(Label lbl)
{
    if (!lbl) return;
    free(lbl->mark);
    free(lbl);
}
