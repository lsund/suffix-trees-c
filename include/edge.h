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
    LabelPointer lbl;
    struct edge *child;
    struct edge *right;
    int leaf_number;
} Edge, *EdgePointer;

void edge_mark(const EdgePointer e, char *mark);

EdgePointer edge_leaf(const char *text, int i, int j, int k);

EdgePointer edge(const char *text, int i, int j);

EdgePointer edge_new_leaf(const char c, int k);

EdgePointer edge_from_label(const LabelPointer lbl);

#endif
