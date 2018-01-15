#ifndef STREE_H
#define STREE_H

#include "edge.h"

typedef Edge STree;

typedef struct treematching {
    Edge end;
    Matching m;
} TreeMatching;

///////////////////////////////////////////////////////////////////////////////
// Functions

TreeMatching stree_find(STree tree, Label l);

Edge stree_init(const char *t);

int stree_es_with(STree tree, char c);

int stree_ec_with(STree tree, char c);

void stree_extend_edge_below(STree base, const Edge ext);

void stree_extend_edge_es(STree base, const Edge ext);

void stree_split(TreeMatching tm);

void stree_destroy(STree tree);

#endif
