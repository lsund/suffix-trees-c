#ifndef STREE_H
#define STREE_H

#include "vertex.h"
#include "matching.h"

typedef struct stree2 {
    Vertex r;
    const char *x;
} *STree2;

typedef struct treematching2 {
    Vertex end;
    Matching m;
} TreeMatching2;

///////////////////////////////////////////////////////////////////////////////
// New

STree2 stree_init2(const char *x);

void stree_extend_below(STree2 st, const Vertex v);

TreeMatching2 scan_prefix2(STree2 tree, const Label2 pre);

void stree_mark(char *t, STree2 st, Vertex v);

void stree_split2(TreeMatching2 tm);

#endif
