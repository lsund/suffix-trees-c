#ifndef SUFFIX_TREE_H
#define SUFFIX_TREE_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "edge.h"

typedef struct label {
    char *mark;
    size_t len;
} Label;

typedef struct edge {
    Label lbl;
    struct edge *child;
    struct edge *right;
} Edge, *EdgePointer;

EdgePointer stree_init(char *t);

Label label(char *mark, size_t len);

EdgePointer edge_from_mark(char *mark, size_t len);

EdgePointer edge_from_label(Label lbl);

void add_edge(EdgePointer base, EdgePointer ext);

    void edge_destroy(Edge e);

void edge_print(Edge e);

#endif
