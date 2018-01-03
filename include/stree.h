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
} Edge, *EdgePointer, *STree;

typedef struct treematching {
    EdgePointer end;
    Matching m;
} TreeMatching;

///////////////////////////////////////////////////////////////////////////////
// Functions

const char *edge_str(const EdgePointer e);

EdgePointer edge_from_letter(const char c);

EdgePointer edge_from_string(char *string);

EdgePointer edge_from_label(const Label lbl);

void edge_split(EdgePointer e, char *s);

TreeMatching stree_find(STree tree, char *marking);

EdgePointer stree_init(const char *t);

int stree_match_letter(STree tree, size_t o, char c);

int stree_sibling_with(STree tree, char c);

int stree_child_with(STree tree, char c);

void stree_extend_edge_below(STree base, const EdgePointer ext);

void stree_extend_edge_right(STree base, const EdgePointer ext);

void stree_destroy(STree tree);

void treematching_destroy(TreeMatching tm);

#endif
