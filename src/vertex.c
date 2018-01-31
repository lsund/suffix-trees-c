
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
    Vertex child = v->c;
    return label2(child->i, child->j);
}


void vertex_extend_below(Vertex v, const Vertex c)
{
    int tmp = v->k;
    if (!v->c) {
        v->c = c;
        c->p = v;

    } else {

        Vertex scan = v->c;
        while (scan->s) {
            scan = scan->s;
        }

        scan->s = c;
        c->p = v;

    }

    v->k = -1;
    if (c->k == -1) {
        c->k = tmp;
    }

}


void vertex_destroy(Vertex v)
{
    free(v);
}
