
#include "vertex.h"

Vertex vertex_root()
{
    return vertex_leaf(-1, -1, -1);
}


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


int vertex_is_root(const Vertex v)
{
    return v->i == -1 && v->j == -1;
}


int vertex_n_siblings(const Vertex v)
{
    int n = 0;
    Vertex scan = v->c;
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
