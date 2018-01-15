#include "stree.h"


STree stree_init(const char *t)
{
    return edge_leaf(t, 0, 1, 0);
}


TreeMatching stree_find(STree tree, Label lbl)
{

    Matching m = match(tree->lbl, lbl);

    TreeMatching ret;
    ret.m = matching_empty();
    ret.end = NULL;

    switch (match_type(m)) {
        case NONE:
            // The first character of c could not be matched with any character
            // in the label of the tree
            if (tree->sibling) {
                return stree_find(tree->sibling, lbl);
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

    Edge probe = tree;

    while(probe) {
        if (label_char_at(probe->lbl, 0) == c) {
            return 1;
        }
        probe = probe->sibling;
    }
    return 0;
}


int stree_child_with(STree tree, char c)
{
    Edge probe = tree->child;
    while(probe) {
        if (label_char_at(probe->lbl, 0) == c) {
            return 1;
        }
        probe = probe->sibling;
    }
    return 0;
}


void stree_extend_edge_below(STree tree, const Edge ext)
{
    int tmp = tree->leaf_number;
    if (!tree->child) {
        tree->child = ext;
    } else {
        Edge probe = tree->child;
        while (probe->sibling) {
            probe = probe->sibling;
        }
        probe->sibling = ext;
    }
    tree->leaf_number = -1;
    if (ext->leaf_number == -1) {
        ext->leaf_number = tmp;
    }
}


void stree_extend_edge_sibling(STree tree, const Edge ext)
{
    Edge probe = tree;

    while (probe->sibling) {
        probe = probe->sibling;
    }

    probe->sibling = ext;
}


void stree_split(TreeMatching tm)
{

    /* printf("%d\n", tm.m.size); */
    int j = tm.end->lbl->j;
    label_set_right(tm.end->lbl, tm.m.size + tm.end->lbl->i);
    /* printf("%d %d\n", tm.end->lbl->i, tm.end->lbl->j); */

    Edge child = edge(tm.end->lbl->text, tm.m.size + tm.end->lbl->i, j);
    /* printf("above: "); */
    /* label_print(tm.end->lbl); */
    /* printf("below: "); */
    /* label_print(child->lbl); */

    stree_extend_edge_below(tm.end, child);
}


void stree_destroy(STree tree)
{
    if (tree) {
        if (tree->child) {
            stree_destroy(tree->child);
        }
        if (tree->sibling) {
            stree_destroy(tree->sibling);
        }
        label_destroy(tree->lbl);
        free(tree);
    }
}
