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


// This represents both the edge itself and a suffix tree due to its recursive
// nature.
typedef struct edge {
    Label lbl;
    struct edge *child;
    struct edge *right;
    int leaf_number;
} *Edge;

Edge edge_leaf(const char *s, int i, int j, int k);

Edge edge(const char *s, int i, int j);

Edge edge_from_label(const Label lbl);

void edge_mark(const Edge e, char *mark);

#endif
