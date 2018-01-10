#include "edge.h"


///////////////////////////////////////////////////////////////////////////////
// Allocs

EdgePointer edge_leaf(char *text, int i, int j, int k)
{
    LabelPointer lbl = label(text, i, j);
    EdgePointer ret = edge_from_label(lbl);
    ret->leaf_number = k;
    return ret;
}

EdgePointer edge(char *text, int i, int j)
{
    return edge_leaf(text, i, j, -1);
}


EdgePointer edge_new_leaf(char c, int k)
{
    char *mark = malloc(sizeof(char) * 8);
    sprintf(mark, "%c", c);
    LabelPointer lbl = label_full(mark);
    EdgePointer ret = edge_from_label(lbl);
    ret->leaf_number = k;
    return ret;
}


EdgePointer edge_from_string(char *s)
{
    char *mark = malloc(sizeof(char) * STRING_INIT_LEN);
    sprintf(mark, "%s", s);
    LabelPointer lbl = label_full(mark);
    return edge_from_label(lbl);
}


EdgePointer edge_from_substring(int i, int n, const char *s)
{
    char *mark = malloc(sizeof(char) * STRING_INIT_LEN);
    sstring(mark, i, n, s);
    LabelPointer lbl = label_full(mark);
    return edge_from_label(lbl);
}


EdgePointer edge_from_label(const LabelPointer lbl)
{
    EdgePointer ret;
    ret              = malloc(sizeof(Edge));
    ret->lbl         = lbl;
    ret->child       = NULL;
    ret->right       = NULL;
    ret->leaf_number = -1;

    return ret;
}


///////////////////////////////////////////////////////////////////////////////
// Edge Functions


void edge_mark(const EdgePointer e, char *mark)
{
    label_mark(e->lbl, mark);
}
