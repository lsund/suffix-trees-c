#include "stree.h"

///////////////////////////////////////////////////////////////////////////////
// Edge


EdgePointer edge_from_letter(char c)
{
    char *cs = malloc(sizeof(char) * 8);
    sprintf(cs, "%c", c);
    return edge_from_string(cs);
}


EdgePointer edge_from_string(char *string)
{
    Label lbl = label(string);
    return edge_from_label(lbl);
}


EdgePointer edge_from_label(const Label lbl)
{
    EdgePointer ret;
    ret = malloc(sizeof(Edge));
    ret->lbl = lbl;
    ret->child = NULL;
    ret->right = NULL;

    return ret;
}


const char *edge_str(const EdgePointer e)
{
    return e->lbl->mark;
}


void edge_split(EdgePointer e, char *s)
{
    Matching m = match(e->lbl->mark, s);

    char *new_m = malloc(sizeof(char) * STRING_INIT_LEN);
    char *child_m = malloc(sizeof(char) * STRING_INIT_LEN);

    sstring(new_m, 0, m.match_both, s);
    sstring(child_m, m.match_both, strlen(e->lbl->mark), e->lbl->mark);

    e->lbl = label(new_m);
    EdgePointer child = edge_from_string(child_m);

    stree_extend_edge_below(e, child);
}


///////////////////////////////////////////////////////////////////////////////
// Suffix Tree


STree stree_init(const char *t)
{
    char *mark = malloc(sizeof(char) * STRING_INIT_LEN);
    sprintf(mark, "%c", t[0]);
    Label lbl = label(mark);

    EdgePointer ret = edge_from_label(lbl);

    return ret;
}


TreeMatching stree_find(STree tree, char *marking)
{

    Matching m = match(tree->lbl->mark, marking);

    TreeMatching ret;
    ret.m = matching_empty();
    ret.end = NULL;

    switch (match_type(m)) {
        case NONE:
            // The first character of c could not be matched with any character
            // in the label of the tree
            if (tree->right) {
                return stree_find(tree->right, marking);
            } else {
                return ret;
            }
        case PARTIAL_RIGHT:
            // The whole marking of the tree label was matched, but something
            // in c is left. Try to continue with child nodes.
            if (tree->child) {
                char *rest = malloc(sizeof(char) * STRING_INIT_LEN);
                sstring(rest, m.match_both, strlen(marking), marking);
                return stree_find(tree->child, rest);
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


void treematching_destroy(TreeMatching tm)
{
    matching_destroy(tm.m);
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
