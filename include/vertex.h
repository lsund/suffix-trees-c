#ifndef VERTEX_H
#define VERTEX_H

#include "label.h"

typedef struct vertex {
    Label2 l;
    struct vertex *c;
    struct vertex *s;
    struct vertex *p;
    int k;
} *Vertex;

Vertex vertex_root();

Vertex vertex(const int i, const int j);

Vertex vertex_leaf(const int i, const int j, const int k);

int vertex_n_siblings(const Vertex e);

void vertex_extend_below(Vertex v, const Vertex c);

void vertex_extend_right(Vertex v, Vertex s);

void vertex_mark(char *t, Vertex v, const char *x);

int vertex_is_root(const Vertex v);

char vertex_char_at(const char *x, Vertex v, int i);

#endif
