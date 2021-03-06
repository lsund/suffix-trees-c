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

int vertex_branches_with(const char *x, const Vertex v, const char c);

int vertex_sibling_with(const char *x, const Vertex v, const char c);

int vertex_children_equals(const char *x, Vertex v1, Vertex v2);

int vertex_equals(const char *x, Vertex v1, Vertex v2);

int vertex_isomorphic(const char *x, Vertex v1, Vertex v2);

void vertex_permute(Vertex v, int i);

void vertex_permute_inverse(Vertex v, int i);

void vertex_print(const Vertex v);

#endif
