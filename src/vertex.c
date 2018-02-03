
#include "vertex.h"

Vertex vertex_root()
{
    return vertex_leaf(-1, -1, 0);
}


Vertex vertex(const int i, const int j)
{
    return vertex_leaf(i, j, -1);
}


Vertex vertex_leaf(const int i, const int j, const int k)
{
    Vertex v;
    v = malloc(sizeof(struct vertex));
    v->l = label2(i, j);
    v->k = k;
    v->c = NULL;
    v->s = NULL;
    v->p = NULL;

    return v;
}


int vertex_is_root(const Vertex v)
{
    return label_is_undefined(v->l);
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


void vertex_extend_right(Vertex v, Vertex s)
{

    Vertex scan = v;

    while (scan->s) {
        scan = scan->s;
    }

    scan->s = s;
    s->p = v->p;

}


void vertex_mark(char *t, Vertex v, const char *x)
{
    if (vertex_is_root(v)) {
        strcpy(t, "r");
    } else {
        label_mark2(t, v->l, x);
    }
}


char vertex_char_at(const char *x, Vertex v, int i)
{
    return label_char_at_2(x, v->l, i);
}


void vertex_destroy(Vertex v)
{
    free(v);
}


int vertex_branches_with(const char *x, const Vertex v, const char c)
{
    Vertex scan = v->c;
    while(scan) {
        if (label_char_at_2(x, scan->l, 0) == c) {
            return 1;
        }
        scan = scan->s;
    }
    return 0;
}


int vertex_sibling_with(const char *x, const Vertex v, const char c)
{
    if (!v) return 1;

    Vertex scan = v;

    while(scan) {
        if (label_char_at_2(x, scan->l, 0) == c) {
            return 1;
        }
        scan = scan->s;
    }
    return 0;
}
