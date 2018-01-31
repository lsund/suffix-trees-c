#ifndef STREE_H
#define STREE_H

#include "edge.h"
#include "vertex.h"

typedef Edge STree;

typedef struct treematching {
    Edge end;
    Matching m;
} TreeMatching;

typedef struct stree2 {
    Vertex r;
    const char *x;
} *STree2;

typedef struct treematching2 {
    Vertex end;
    Matching m;
} TreeMatching2;

///////////////////////////////////////////////////////////////////////////////
// Functions

TreeMatching scan_prefix(STree tree, Label l);

Edge stree_init(const char *t);

int stree_sibling_with(STree tree, char c);

int stree_child_with(STree tree, char c);

void stree_extend_edge_below(STree base, const Edge ext);

void stree_extend_edge_sibling(STree base, const Edge ext);

void stree_split(TreeMatching tm);

void stree_destroy(STree tree);

///////////////////////////////////////////////////////////////////////////////
// New

STree2 stree_init2(const char *x);

void stree_extend_below(STree2 st, const Vertex v);

TreeMatching2 scan_prefix2(STree2 tree, const Label2 pre);

#endif
