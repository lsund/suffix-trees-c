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


void label_extend_letter(Label lbl, const char mark)
{
    char buf[2];
    buf[0] = mark;
    label_extend(lbl, buf);
}


void label_extend(Label lbl, const char *mark)
{

    size_t mark_len = strlen(mark);

    if (lbl->len + mark_len > lbl->max_len) {
        char tmp[lbl->len];
        sprintf(tmp, "%s", lbl->mark);

        free(lbl->mark);
        lbl->max_len *= 2;
        lbl->mark    = NULL;
        lbl->mark    = malloc(sizeof(char) * lbl->max_len * 2);

        sprintf(lbl->mark, "%s", tmp);
    }

    lbl->len += mark_len;
    strcat(lbl->mark, mark);
}
