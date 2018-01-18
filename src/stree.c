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
    int j;
    int n = 0;
    int ord[64];
    char seq[STRING_MAX_LEN];
    char perm[STRING_MAX_LEN];
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
    if (i > factorial(n) - 1) {
        runtime_error("stree_permute: permutation index too damn high!");
        return;
    }

    nat_sequence(n, seq);
    nth_permutation(i, seq, perm);

    for (j = 0; j < n; j++) {
        ord[j] = char_to_int(perm[j]);
    }

    tree->c = siblings[ord[0]];

    for (j = 0; j < n - 1; j++) {
        siblings[ord[j]]->s = siblings[ord[j + 1]];
    }

    siblings[ord[n - 1]]->s = NULL;

}


void stree_permute_inverse(STree t, int i)
{
    int n = 0;
    Edge probe = t->c;
    while (probe) {
        probe = probe->s;
        n++;
    }
    stree_permute(t, permutation_inverse_number(i, n));
}


int stree_equals(STree t1, STree t2)
{
    if (t1 && t2) {

        char tmp1[STRING_MAX_LEN];
        char tmp2[STRING_MAX_LEN];
        edge_mark(t1, tmp1);
        edge_mark(t2, tmp2);
        if (strcmp(tmp1, tmp2) != 0) {
            return 0;
        } else {
            return stree_equals(t1->c, t2->c) && stree_equals(t1->s, t2->s);
        }

    } else {
        return !t1 && !t2;
    }
}


static int stree_isomorphic_aux(STree t1, STree t2, int n, int i)
{
    if (i > factorial(n) - 1) {
        return 0;
    }
    if (stree_equals(t1, t2)) {
        return 1;
    } else {
        stree_permute(t2, i);

        if (stree_equals(t1, t2)) {
            stree_permute_inverse(t2, i);
            return 1;
        } else {
            stree_permute_inverse(t2, i);
        }

    }
    return stree_isomorphic_aux(t1, t2, n, ++i);
}


int stree_isomorphic(STree t1, STree t2)
{
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
