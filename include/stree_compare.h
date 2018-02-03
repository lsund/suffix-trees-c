#ifndef STREE_COMPARE_H
#define STREE_COMPARE_H

#include "stree.h"
#include "stree_permute.h"

int stree_root_equals(STree t1, STree t2);

int stree_children_equals(STree t1, STree t2);

int stree_equals(STree t1, STree t2);

int stree_isomorphic(STree t1, STree t2);

///////////////////////////////////////////////////////////////////////////////
// New

int stree_children_equals2(STree2 t1, STree2 t2);

int stree_equals2(STree2 t1, STree2 t2);

int stree_isomorphic2(STree2 t1, STree2 t2);

#endif
