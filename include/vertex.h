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

int vertex_n_siblings(const Vertex e);

void label_mark2(char *t, const Vertex v1, const Vertex v2, const char *s);

Label2 vertex_label_below(Vertex v);

#endif
