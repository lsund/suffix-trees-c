#include "stree.h"

///////////////////////////////////////////////////////////////////////////////
// Allocs


EdgePointer edge_from_letter(char c)
{
    char *mark = malloc(sizeof(char) * 8);
    sprintf(mark, "%c", c);
    LabelPointer lbl = label(mark);
    return edge_from_label(lbl);
}


EdgePointer edge_from_string(char *s)
{
    char *mark = malloc(sizeof(char) * STRING_INIT_LEN);
    sprintf(mark, "%s", s);
    LabelPointer lbl = label(mark);
    return edge_from_label(lbl);
}


EdgePointer edge_from_substring(int i, int n, char *s)
{
    char *mark = malloc(sizeof(char) * STRING_INIT_LEN);
    sstring(mark, i, n, s);
    LabelPointer lbl = label(mark);
    return edge_from_label(lbl);
}


EdgePointer edge_from_label(const LabelPointer lbl)
{
    EdgePointer ret;
    ret = malloc(sizeof(Edge));
    ret->lbl = lbl;
    ret->child = NULL;
    ret->right = NULL;

    return ret;
}


///////////////////////////////////////////////////////////////////////////////
// Edge Functions


const char *edge_str(const EdgePointer e)
{
    return e->lbl->mark;
}


void edge_split(TreeMatching tm)
{
    size_t len = tm.end->lbl->len;
    char *mark = tm.end->lbl->mark;

    char *new = malloc(sizeof(char) * STRING_INIT_LEN);
    sstring(new, 0, tm.m.size, tm.end->lbl->mark);
    /* LabelPointer newlabel = label(new); */

    tm.end->lbl->n = tm.m.size;
    // TODO Need to replace all accesses to lbl->mark with correct indexed gets
    tm.end->lbl->mark = new;

    EdgePointer child = edge_from_substring(tm.m.size, len, mark);

    stree_extend_edge_below(tm.end, child);
}


///////////////////////////////////////////////////////////////////////////////
// Suffix Tree


STree stree_init(const char *t)
{
    return edge_from_letter(t[0]);
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
                lbl->i += m.size;
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
