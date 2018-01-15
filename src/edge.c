#include "edge.h"


Edge edge(const char *s, const int i, const int j)
{
    return edge_leaf(s, i, j, -1);
}


Edge edge_leaf(const char *s, const int i, const int j, const int k)
{
    Label lbl = label(s, i, j);
    Edge ret = edge_from_label(lbl);
    ret->leaf_number = k;
    return ret;
}


Edge edge_from_label(const Label lbl)
{
    Edge ret;
    ret              = malloc(sizeof(struct edge));
    ret->lbl         = lbl;
    ret->child       = NULL;
    ret->sibling     = NULL;
    ret->leaf_number = -1;

    return ret;
}


void edge_mark(const Edge e, char *t)
{
    if (e) {
        label_mark(e->lbl, t);
    } else {
        t[0] = '\0';
    }
}
