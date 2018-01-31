#ifndef VERTEX_H
#define VERTEX_H

#include "label.h"

typedef struct vertex {
    int i, j;
    struct vertex *c;
    struct vertex *s;
    struct vertex *p;
    int k;
} *Vertex;

Vertex vertex_root();

Vertex vertex(const int i, const int j);

Vertex vertex_leaf(const int i, const int j, const int k);

int vertex_n_siblings(const Vertex e);

Label2 vertex_label_below(Vertex v);

void vertex_extend_below(Vertex v, const Vertex c);

#endif
