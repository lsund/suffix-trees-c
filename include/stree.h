#ifndef STREE_H
#define STREE_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#include "config.h"
#include "util.h"
#include "matching.h"
#include "label.h"


// This represents both the edge itself and a suffix tree due to its recursive
// nature.
typedef struct edge {
    Label lbl;
    struct edge *child;
    struct edge *right;
} Edge, *EdgePointer, *Stree;


///////////////////////////////////////////////////////////////////////////////
// Functions

const char *edge_str(const EdgePointer e);

EdgePointer edge_from_mark(char *mark);

EdgePointer edge_from_label(const Label lbl);

Matching edge_match_marking(EdgePointer e, const char *m);

EdgePointer stree_find(Stree tree, const char *m);

EdgePointer stree_init(const char *t);

void stree_extend(Stree base, const EdgePointer ext);

void stree_extend_right(Stree base, const EdgePointer ext);

#endif
