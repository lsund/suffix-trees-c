#ifndef STREE_H
#define STREE_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "util.h"

///////////////////////////////////////////////////////////////////////////////
// Structs


typedef struct label {
    char *mark;
    size_t len;
} Label;

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

int edge_match_marking(EdgePointer e, const char *m);

EdgePointer stree_init(const char *t);

void stree_extend(EdgePointer base, const EdgePointer ext);

#endif
