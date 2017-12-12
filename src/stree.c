#include "stree.h"

///////////////////////////////////////////////////////////////////////////////
// Edge


EdgePointer edge_from_mark(char *mark)
{
    EdgePointer ret;
    Label lbl = label(mark);
    ret = malloc(sizeof(Edge));
    ret->lbl = lbl;
    ret->child = NULL;

    return ret;
}


EdgePointer edge_from_label(const Label lbl)
{
    EdgePointer ret;
    ret = malloc(sizeof(Edge));
    ret->lbl = lbl;
    ret->child = NULL;

    return ret;
}


const char *edge_str(const EdgePointer e)
{
    return e->lbl->mark;
}


Matching edge_match_marking(const EdgePointer e, const char *m)
{
    return match(e->lbl->mark, m);
}


Matching marking_match_edge(const EdgePointer e, const char *m)
{
    return match(m, e->lbl->mark);
}
///////////////////////////////////////////////////////////////////////////////
// Suffix Tree


EdgePointer stree_find(Stree tree, const char *m)
{

    // TODO Does not continue to child not ATM

    Matching match = marking_match_edge(tree, m);

    switch (match_type(match)) {
        case NONE:
            if (tree->right) {
                return stree_find(tree->right, m);
            } else {
                return NULL;
            }
            break;
        case PARTIAL:
            return tree;
            break;
        case EXACT:
            return tree;
    }

    return NULL;
}


EdgePointer stree_init(const char *t)
{
    char *mark = malloc(sizeof(char) * STRING_INIT_LEN);
    sprintf(mark, "%c", t[0]);
    Label l =label(mark);

    EdgePointer ret = edge_from_label(l);

    return ret;
}


void stree_extend(Stree base, const EdgePointer ext)
{
    if (!base->child) {
        base->child = ext;
    } else {
        EdgePointer probe = base->child;
        while (probe->right) {
            probe = probe->right;
        }
        probe->right = ext;
    }
}


void stree_extend_right(Stree base, const EdgePointer ext)
{
    EdgePointer probe = base;
    while (probe->right) {
        probe = probe->right;
    }
    probe->right = ext;
}
