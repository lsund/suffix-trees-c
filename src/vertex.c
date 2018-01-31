
#include "vertex.h"

Vertex vertex(const int i, const int j)
{
    return vertex_leaf(i, j, -1);
}

Vertex vertex_leaf(const int i, const int j, const int k)
{
    Vertex v;
    v = malloc(sizeof(struct vertex));
    v->i = i;
    v->j = j;
    v->k = k;
    v->c = NULL;
    v->s = NULL;
    v->p = NULL;

    return v;
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


Label2 vertex_label_below(Vertex v)
{
    return label2(v->i, v->c->i);
}


void vertex_destroy(Vertex v)
{
    free(v);
}
