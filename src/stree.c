#include "stree.h"


STree stree_init(const char *t)
{
    return edge_leaf(t, 0, 1, 0);
}


TreeMatching stree_find(STree tree, LabelPointer lbl)
{

    Matching m = match(tree->lbl, lbl);

    TreeMatching ret;
    ret.m = matching_empty();
    ret.end = NULL;

    switch (match_type(m)) {
        case NONE:
            // The first character of c could not be matched with any character
            // in the label of the tree
            if (tree->right) {
                return stree_find(tree->right, lbl);
            } else {
                return ret;
            }
        case PARTIAL_RIGHT:
            // The whole mark of the tree label was matched, but something
            // in c is left. Try to continue with child nodes.
            if (tree->child) {
                label_shrink_left(lbl, m.size);
                return stree_find(tree->child, lbl);
            } else {
                return ret;
            }
        case PARTIAL_LEFT:
            // The whole c was matched but ended up in the middle of the tree
            // label.
            ret.m = m;
            ret.end = tree;
            return ret;
        case EXACT:
            ret.m = m;
            ret.end = tree;
            return ret;
    }

    return ret;
}


int stree_sibling_with(STree tree, char c)
{
    if (!tree) return 1;

    EdgePointer probe = tree;

    while(probe) {
        if (label_char_at(probe->lbl, 0) == c) {
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
        if (label_char_at(probe->lbl, 0) == c) {
            return 1;
        }
        probe = probe->right;
    }
    return 0;
}


void stree_extend_edge_below(STree tree, const EdgePointer ext)
{
    int tmp = tree->leaf_number;
    if (!tree->child) {
        tree->child = ext;
    } else {
        EdgePointer probe = tree->child;
        while (probe->right) {
            probe = probe->right;
        }
        probe->right = ext;
    }
    tree->leaf_number = -1;
    if (ext->leaf_number == -1) {
        ext->leaf_number = tmp;
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


void stree_split(TreeMatching tm)
{

    int j = tm.end->lbl->j;
    label_set_right(tm.end->lbl, tm.m.size);

    EdgePointer child = edge_from_substring(tm.m.size, j, tm.end->lbl->text);

    stree_extend_edge_below(tm.end, child);
}


void stree_destroy(STree tree)
{
    if (tree) {
        if (tree->child) {
            stree_destroy(tree->child);
        }
        if (tree->right) {
            stree_destroy(tree->right);
        }
        label_destroy(tree->lbl);
        free(tree);
    }
}
