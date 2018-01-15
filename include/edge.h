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
    Label l;
    struct edge *child;
    struct edge *sibling;
    int k;
} *Edge;

Edge edge(const char *s, const int i, const int j);

Edge edge_leaf(const char *s, const int i, const int j, const int k);

Edge edge_from_label(const Label l);

void edge_mark(const Edge e, char *mark);

#endif
