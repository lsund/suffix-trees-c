#ifndef STREE_H
#define STREE_H

#include "edge.h"

typedef EdgePointer STree;

typedef struct treematching {
    EdgePointer end;
    Matching m;
} TreeMatching;

///////////////////////////////////////////////////////////////////////////////
// Functions

TreeMatching stree_find(STree tree, LabelPointer lbl);

EdgePointer stree_init(const char *t);

int stree_sibling_with(STree tree, char c);

int stree_child_with(STree tree, char c);

void stree_extend_edge_below(STree base, const EdgePointer ext);

void stree_extend_edge_right(STree base, const EdgePointer ext);

void stree_split(TreeMatching tm);

void stree_destroy(STree tree);

#endif
