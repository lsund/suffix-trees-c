#include "stree.h"

///////////////////////////////////////////////////////////////////////////////
// Edge


EdgePointer edge_from_letter(char c)
{
    char *cs = malloc(sizeof(char) * 2);
    *cs = c;
    return edge_from_string(cs);
}


EdgePointer edge_from_string(const char *string)
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


void edge_split(EdgePointer e, const char *s)
{
    Matching m = match(e->lbl->mark, s);
    free(e->lbl);
    e->lbl = label(m.match);
    EdgePointer child = edge_from_string(m.rest_left);
    stree_extend_edge_below(e, child);
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


int stree_sibling_with(STree tree, char c)
{
    EdgePointer probe = tree;
    while(probe) {
        if (*probe->lbl->mark == c) {
            return 1;
        }
        probe = probe->right;
    }
    return 0;
}


int stree_child_with(STree tree, char c)
{
    EdgePointer probe = tree->child;
    while(probe) {
        if (*probe->lbl->mark == c) {
            return 1;
        }
        probe = probe->right;
    }
    return 0;
}


int stree_match_letter(STree tree, size_t o, char c)
{
    size_t len = tree->lbl->len;
    if (o > len) {
        return runtime_error("stree_match_letter: offset longer than length");
    } else if (o == len) {
        return stree_child_with(tree, c);
    } else {
        return tree->lbl->mark[o + 1] == c;
    }
}


void stree_extend_edge_below(STree tree, const EdgePointer ext)
{
    if (!tree->child) {
        tree->child = ext;
    } else {
        EdgePointer probe = tree->child;
        while (probe->right) {
            probe = probe->right;
        }
        probe->right = ext;
    }
}


void stree_extend_edge_right(STree tree, const EdgePointer ext)
{
    EdgePointer probe = tree;
    while (probe->right) {
        probe = probe->right;
    }
    probe->right = ext;
}
