#include "edge.h"


///////////////////////////////////////////////////////////////////////////////
// Allocs


EdgePointer edge_empty()
{
    EdgePointer ret;
    ret        = malloc(sizeof(Edge));
    ret->lbl   = NULL;
    ret->child = NULL;
    ret->right = NULL;
    return ret;
}


EdgePointer edge_from_letter(char c)
{
    char *mark = malloc(sizeof(char) * 8);
    sprintf(mark, "%c", c);
    LabelPointer lbl = label(mark);
    return edge_from_label(lbl);
}


EdgePointer edge_from_string(char *s)
{
    char *mark = malloc(sizeof(char) * STRING_INIT_LEN);
    sprintf(mark, "%s", s);
    LabelPointer lbl = label(mark);
    return edge_from_label(lbl);
}


EdgePointer edge_from_substring(int i, int n, char *s)
{
    char *mark = malloc(sizeof(char) * STRING_INIT_LEN);
    sstring(mark, i, n, s);
    LabelPointer lbl = label(mark);
    return edge_from_label(lbl);
}


EdgePointer edge_from_label(const LabelPointer lbl)
{
    EdgePointer ret;
    ret = malloc(sizeof(Edge));
    ret->lbl = lbl;
    ret->child = NULL;
    ret->right = NULL;

    return ret;
}


///////////////////////////////////////////////////////////////////////////////
// Edge Functions


const char *edge_str(const EdgePointer e)
{
    return e->lbl->mark;
}
