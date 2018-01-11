#include "edge.h"


///////////////////////////////////////////////////////////////////////////////
// Allocs

EdgePointer edge_leaf(const char *text, int i, int j, int k)
{
    LabelPointer lbl = label(text, i, j);
    EdgePointer ret = edge_from_label(lbl);
    ret->leaf_number = k;
    return ret;
}

EdgePointer edge(const char *text, int i, int j)
{
    return edge_leaf(text, i, j, -1);
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
