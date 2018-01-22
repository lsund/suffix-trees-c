#ifndef EDGE_H
#define EDGE_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#include "config.h"
#include "util.h"
#include "label.h"
#include "matching.h"

/*
 * struct edge
 *
 * Label l        : the edge label
 * struct edge *c : The child pointer
 * struct edge *s : The sibling pointer
 * int k          : The leaf number (-1 if not a leaf)
 *
 */
typedef struct edge {
    Label l;
    struct edge *c;
    struct edge *s;
    int k;
} *Edge;

Edge edge(const char *s, const int i, const int j);

Edge edge_leaf(const char *s, const int i, const int j, const int k);

Edge edge_from_label(const Label l);

void edge_mark(const Edge e, char *mark);

int edge_n_siblings(const Edge e);

#endif
