#ifndef VERTEX_H
#define VERTEX_H

#include "label.h"

typedef struct vertex {
    int i;
    struct vertex *c;
    struct vertex *s;
    struct vertex *p;
    int k;
} *Vertex;

Vertex vertex(const int i);

Vertex vertex_leaf(const int i, const int k);

void edge_mark2(const char *s, const Vertex v1, const Vertex v2, char *mark);

int vertex_n_siblings(const Vertex e);

#endif
