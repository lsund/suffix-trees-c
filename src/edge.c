#include "edge.h"


Edge edge(const char *s, const int i, const int j)
{
    return edge_leaf(s, i, j, -1);
}


Edge edge_leaf(const char *s, const int i, const int j, const int k)
{
    Label l = label(s, i, j);
    Edge ret = edge_from_label(l);
    ret->k = k;

    return ret;
}


Edge edge_from_label(const Label l)
{
    Edge ret;
    ret          = malloc(sizeof(struct edge));
    ret->l     = l;
    ret->child   = NULL;
    ret->sibling = NULL;
    ret->k       = -1;

    return ret;
}


void edge_mark(const Edge e, char *t)
{
    if (e) {
        label_mark(e->l, t);
    } else {
        t[0] = '\0';
    }
}
