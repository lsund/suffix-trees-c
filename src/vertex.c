
#include "vertex.h"

Vertex vertex(const int i)
{
    return vertex_leaf(i, -1);
}

Vertex vertex_leaf(const int i, const int k)
{
    Vertex v;
    v = malloc(sizeof(struct vertex));
    v->i = i;
    v->k = k;
    v->c = NULL;
    v->s = NULL;
    v->p = NULL;

    return v;
}


void edge_mark2(const char *s, const Vertex v1, const Vertex v2, char *mark)
{
    sstring(mark, v1->i, v2->i - v1->i, s);
}


int vertex_n_siblings(const Vertex e)
{
    int n = 0;
    Vertex scan = e->c;
    while (scan) {
        scan = scan->s;
        n++;
    }
    return n;
}
