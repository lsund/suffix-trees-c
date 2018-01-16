#include "stree.h"


STree stree_init(const char *t)
{
    return edge_leaf(t, 0, 1, 0);
}

// TODO rename to scan_prefix
TreeMatching stree_find(STree tree, Label l)
{

    Matching m = match(tree->l, l);

    TreeMatching ret;
    ret.m = matching_empty();
    ret.end = NULL;

    switch (match_type(m)) {
        case NONE:
            // The first character of c could not be matched with any character
            // in the label of the tree
            if (tree->s) {
                return stree_find(tree->s, l);
            } else {
                return ret;
            }
        case PARTIAL_RIGHT:
            // The whole mark of the tree label was matched, but something
            // in c is left. Try to continue with ec nodes.
            if (tree->c) {
                label_shrink_left(l, m.n);
                return stree_find(tree->c, l);
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
        if (label_char_at(probe->l, 0) == c) {
            return 1;
        }
        probe = probe->s;
    }
    return 0;
}


int stree_child_with(STree tree, char c)
{
    Edge probe = tree->c;
    while(probe) {
        if (label_char_at(probe->l, 0) == c) {
            return 1;
        }
        probe = probe->s;
    }
    return 0;
}


void stree_extend_edge_below(STree tree, const Edge ext)
{
    int tmp = tree->k;
    if (!tree->c) {
        tree->c = ext;
    } else {
        Edge probe = tree->c;
        while (probe->s) {
            probe = probe->s;
        }
        probe->s = ext;
    }
    tree->k = -1;
    if (ext->k == -1) {
        ext->k = tmp;
    }
}


void stree_extend_edge_sibling(STree tree, const Edge ext)
{
    Edge probe = tree;

    while (probe->s) {
        probe = probe->s;
    }

    probe->s = ext;
}


void stree_split(TreeMatching tm)
{
    int j = tm.end->l->j;
    label_set_right(tm.end->l, tm.m.n + tm.end->l->i);

    Edge c = edge(tm.end->l->s, tm.m.n + tm.end->l->i, j);

    stree_extend_edge_below(tm.end, c);
}


void stree_permute(STree tree, int i)
{
    int n = 0;
    char s[STRING_MAX_LEN];
    char p[STRING_MAX_LEN];
    Edge siblings[64], probe;

    probe = tree->c;
    while (probe) {
        siblings[n] = probe;
        probe = probe->s;
        n++;
    }
    if (!n) {
        return;
    }

    char *set = "01";
    strcpy(s, set);

    nth_permutation(i, s, p);

    size_t j;
    int order[64];
    for (j = 0; j < strlen(set); j++)
    {
        order[j] = char_to_int(p[j]);
    }

    tree->c = siblings[order[0]];
    for (j = 0; j < strlen(set) - 1; j++)
    {
        siblings[order[j]]->s = siblings[order[j + 1]];
    }
    siblings[order[strlen(set) - 1]]->s = NULL;

}


void stree_destroy(STree tree)
{
    if (tree) {
        if (tree->c) {
            stree_destroy(tree->c);
        }
        if (tree->s) {
            stree_destroy(tree->s);
        }
        label_destroy(tree->l);
        free(tree);
    }
}
