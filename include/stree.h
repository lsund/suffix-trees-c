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
    LabelPointer lbl;
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

EdgePointer edge_from_label(const LabelPointer lbl);

void edge_update_label(EdgePointer e, int i, int n, char *s);

void edge_split(TreeMatching tm);

TreeMatching stree_find(STree tree, LabelPointer lbl);

EdgePointer stree_init(const char *t);

int stree_sibling_with(STree tree, char c);

int stree_child_with(STree tree, char c);

void stree_extend_edge_below(STree base, const EdgePointer ext);

void stree_extend_edge_right(STree base, const EdgePointer ext);

void stree_destroy(STree tree);

#endif
