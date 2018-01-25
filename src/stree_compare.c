
#include "stree_compare.h"


static int stree_children_equals_aux(STree t1, STree t2)
{
    if (t1 && t2 && stree_root_equals(t1, t2)) {
        return stree_children_equals_aux(t1->s, t2->s);
    } else {
        return !t1 && !t2;
    }
}


static int stree_isomorphic_aux(STree t1, STree t2, int n, int i)
{
    if (i > factorial(n) - 1) {
        return 0;
    }

    if (stree_children_equals(t1, t2)) {
        return stree_isomorphic(t1->c, t2->c);
    } else {

        stree_permute(t2, i);

        if (stree_children_equals(t1, t2)) {
            return stree_isomorphic(t1->c, t2->c);
        } else {
            stree_permute_inverse(t2, i);
        }

    }
    return stree_isomorphic_aux(t1, t2, n, ++i);
}


///////////////////////////////////////////////////////////////////////////////
// Public API


int stree_root_equals(STree t1, STree t2)
{
    char tmp1[STRING_MAX_LEN];
    char tmp2[STRING_MAX_LEN];
    edge_mark(t1, tmp1);
    edge_mark(t2, tmp2);
    return strcmp(tmp1, tmp2) == 0;
}


int stree_children_equals(STree t1, STree t2)
{
    return stree_children_equals_aux(t1->c, t2->c);
}

int stree_equals(STree t1, STree t2)
{
    if (t1 && t2 && stree_root_equals(t1, t2)) {

        return stree_equals(t1->c, t2->c) && stree_equals(t1->s, t2->s);

    } else {
        return !t1 && !t2;
    }
}


// TODO Remember structure before permute and return to this
int stree_isomorphic(STree t1, STree t2)
{
    if (t1 && t2) {
        Edge probe1, probe2;
        probe1 = t1->c;
        probe2 = t2->c;
        int n = 0;
        while (probe1 && probe2) {
            probe1 = probe1->s;
            probe2 = probe2->s;
            n++;
        }

        // Do the two root nodes have the same number of children?
        if (probe1 || probe2) {
            return 0;
        } else {
            return stree_isomorphic_aux(t1, t2, n, 0);
        }
    } else {
        return !t1 && !t2;
    }
}


