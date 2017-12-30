#include "stree.h"

///////////////////////////////////////////////////////////////////////////////
// Edge


EdgePointer edge_from_letter(char c)
{
    char *cs = malloc(sizeof(char) * 2);
    *cs = c;
    return edge_from_string(cs);
}


EdgePointer edge_from_string(char *string)
{
    EdgePointer ret;
    Label lbl = label(string);
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


///////////////////////////////////////////////////////////////////////////////
// Suffix Tree


STree stree_init(const char *t)
{
    char *mark = malloc(sizeof(char) * STRING_INIT_LEN);
    sprintf(mark, "%c", t[0]);
    Label l =label(mark);

    EdgePointer ret = edge_from_label(l);

    return ret;
}


TreeMatching stree_find(STree tree, const char *c)
{
    // TODO Rewrite everything
    Matching m = match(tree->lbl->mark, c);

    TreeMatching ret;
    ret.m = matching_empty();
    ret.tree = NULL;

    switch (match_type(m)) {
        case NONE:
            // The first character of c could not be matched with any character
            // in the label of the tree
            if (tree->right) {
                return stree_find(tree->right, c);
            } else {
                return ret;
            }
        case PARTIAL_LEFT:
            // The whole marking of the tree label was matched, but something
            // in c is left. Try to continue with child nodes.
            if (tree->child) {
                return stree_find(tree->child, m.rest_right);
            } else {
                return ret;
            }
        case PARTIAL_RIGHT:
            // The whole c was matched but ended up in the middle of the tree
            // label.
            ret.m = m;
            ret.tree = tree;
            return ret;
        case EXACT:
            ret.m = m;
            ret.tree = tree;
            return ret;
    }

    return ret;
}


void stree_extend_edge_below(STree base, const EdgePointer ext)
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


void stree_extend_edge_right(STree base, const EdgePointer ext)
{
    EdgePointer probe = base;
    while (probe->right) {
        probe = probe->right;
    }
    probe->right = ext;
}
