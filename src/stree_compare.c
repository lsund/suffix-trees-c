
#include "stree_compare.h"


///////////////////////////////////////////////////////////////////////////////
// Public API


int stree_equals2(STree2 t1, STree2 t2)
{
    if (strcmp(t1->x, t2->x) == 0) {
        return vertex_equals(t1->x, t1->r, t2->r);
    } else {
        return 0;
    }
}


int stree_isomorphic2(STree2 t1, STree2 t2)
{
    if (strcmp(t1->x, t2->x) == 0) {
        return vertex_isomorphic(t1->x, t1->r, t2->r);
    } else {
        return 0;
    }
}
