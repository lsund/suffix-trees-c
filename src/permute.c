
#include "stree_permute.h"

void stree_permute2(STree2 st, int i)
{
    return vertex_permute(st->r, i);
}

void stree_permute_inverse2(STree2 st, int i)
{
    return vertex_permute_inverse(st->r, i);
}

