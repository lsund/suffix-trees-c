#include "edge.h"


Edge edge(const char *s, const int i, const int j)
{
    return edge_leaf(s, i, j, -1);
}


Edge edge_leaf(const char *s, const int i, const int j, const int k)
{
    Label l = label(s, i, j);
    Edge e = edge_from_label(l);
    e->k = k;

    return e;
}


Edge edge_from_label(const Label l)
{
    Edge e;

    e    = malloc(sizeof(struct edge));
    e->l = l;
    e->c = NULL;
    e->s = NULL;
    e->k = -1;

    return e;
}


void edge_mark(const Edge e, char *t)
{
    if (e) {
        label_mark(e->l, t);
    } else {
        t[0] = '\0';
    }
}


int edge_n_siblings(const Edge e)
{
    int n = 0;
    Edge scan = e->c;
    while (scan) {
        scan = scan->s;
        n++;
    }
    return n;
}
