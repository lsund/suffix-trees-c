#ifndef STREE_H
#define STREE_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>


///////////////////////////////////////////////////////////////////////////////
// Structs


typedef struct label {
    const char *mark;
    size_t len;
} Label;

typedef struct edge {
    Label lbl;
    struct edge *child;
    struct edge *right;
} Edge, *EdgePointer, *Stree;


///////////////////////////////////////////////////////////////////////////////
// Functions


Label label(const char *mark, const size_t len);

const char *edge_str(const EdgePointer e);

EdgePointer edge_from_mark(const char *mark, const size_t len);

EdgePointer edge_from_label(const Label lbl);

EdgePointer stree_init(const char *t);

void stree_extend(EdgePointer base, const EdgePointer ext);

#endif
