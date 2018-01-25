#ifndef STREE_COMPARE_H
#define STREE_COMPARE_H

#include "stree.h"
#include "stree_permute.h"

int stree_root_equals(STree t1, STree t2);

int stree_children_equals(STree t1, STree t2);

int stree_equals(STree t1, STree t2);

int stree_isomorphic(STree t1, STree t2);

#endif
