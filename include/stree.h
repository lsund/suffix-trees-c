#ifndef STREE_H
#define STREE_H

#include "edge.h"
#include "permute.h"

typedef struct treematching {
    Edge end;
    Matching m;
} TreeMatching;

///////////////////////////////////////////////////////////////////////////////
// Functions

TreeMatching scan_prefix(STree tree, Label l);

Edge stree_init(const char *t);

int stree_sibling_with(STree tree, char c);

int stree_child_with(STree tree, char c);

void stree_extend_edge_below(STree base, const Edge ext);

void stree_extend_edge_sibling(STree base, const Edge ext);

void stree_split(TreeMatching tm);

void stree_permute(STree tree, int i);

int stree_equals(STree t1, STree t2);

int stree_children_equals(STree t1, STree t2);

int stree_isomorphic(STree t1, STree t2);

void stree_destroy(STree tree);

#endif
