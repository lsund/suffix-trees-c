#ifndef STREE_H
#define STREE_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#include "util.h"


///////////////////////////////////////////////////////////////////////////////
// Enums

typedef enum { NONE, EXACT, PARTIAL } MatchType;

///////////////////////////////////////////////////////////////////////////////
// Structs

typedef struct matching {
    const char *match;
    const char *rest;
} Matching;

typedef struct label {
    char *mark;
    size_t len;
} Label;

// This represents both the edge itself and a suffix tree due to its recursive
// nature.
typedef struct edge {
    Label lbl;
    struct edge *child;
    struct edge *right;
} Edge, *EdgePointer, *Stree;


///////////////////////////////////////////////////////////////////////////////
// Functions


Label label(char *mark, const size_t len);

const char *edge_str(const EdgePointer e);

EdgePointer edge_from_mark(char *mark, const size_t len);

EdgePointer edge_from_label(const Label lbl);

MatchType match_type(const Matching match);

Matching edge_match_marking(EdgePointer e, const char *m);

EdgePointer stree_find(Stree tree, const char *m);

EdgePointer stree_init(const char *t);

void stree_extend(Stree base, const EdgePointer ext);

#endif
