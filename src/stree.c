#include "stree.h"


STree stree_init(const char *t)
{
    return edge_leaf(t, 0, 1, 0);
}

TreeMatching scan_prefix(STree st, Label pre)
{

    Matching m = match(st->l, pre);

    TreeMatching ret;
    ret.m = matching_empty();
    ret.end = NULL;

    switch (match_type(m)) {
        case NONE:
            // The first character of c could not be matched with any character
            // in the label of the tree
            if (st->s) {
                return scan_prefix(st->s, pre);
            } else {
                return ret;
            }
        case PARTIAL_RIGHT:
            // The whole mark of the tree label was matched, but something
            // in c is left. Try to continue with ec nodes.
            if (st->c) {
                label_shrink_left(pre, m.n);
                return scan_prefix(st->c, pre);
            } else {
                return ret;
            }
        case PARTIAL_LEFT:
            // The whole c was matched but ended up in the middle of the tree
            // label.
            ret.m = m;
            ret.end = st;
            return ret;
        case EXACT:
            ret.m = m;
            ret.end = st;
            return ret;
    }

    return ret;
}


int stree_sibling_with(STree st, char c)
{
    if (!st) return 1;

    Edge scan = st;

    while(scan) {
        if (label_char_at(scan->l, 0) == c) {
            return 1;
        }
        scan = scan->s;
    }
    return 0;
}


int stree_child_with(STree st, char c)
{
    Edge scan = st->c;
    while(scan) {
        if (label_char_at(scan->l, 0) == c) {
            return 1;
        }
        scan = scan->s;
    }
    return 0;
}


void stree_extend_edge_below(STree st, const Edge ext)
{
    int tmp = st->k;
    if (!st->c) {
        st->c = ext;
    } else {
        Edge scan = st->c;
        while (scan->s) {
            scan = scan->s;
        }
        scan->s = ext;
    }
    st->k = -1;
    if (ext->k == -1) {
        ext->k = tmp;
    }
}


void stree_extend_edge_sibling(STree st, const Edge ext)
{
    Edge scan = st;

    while (scan->s) {
        scan = scan->s;
    }

    scan->s = ext;
}


void stree_split(TreeMatching tm)
{
    int i = tm.end->l->i;
    int j = tm.end->l->j;

    int new_right = tm.m.n + i;

    label_set_right(tm.end->l, new_right);

    Edge c = edge(tm.end->l->s, new_right, j);

    stree_extend_edge_below(tm.end, c);
}


int root_equals(STree t1, STree t2)
{
    char tmp1[STRING_MAX_LEN];
    char tmp2[STRING_MAX_LEN];
    edge_mark(t1, tmp1);
    edge_mark(t2, tmp2);
    return strcmp(tmp1, tmp2) == 0;
}


static int stree_children_equals_aux(STree t1, STree t2)
{
    if (t1 && t2 && root_equals(t1, t2)) {
        return stree_children_equals_aux(t1->s, t2->s);
    } else {
        return !t1 && !t2;
    }
}


int stree_children_equals(STree t1, STree t2)
{
    return stree_children_equals_aux(t1->c, t2->c);
}

int stree_equals(STree t1, STree t2)
{
    if (t1 && t2 && root_equals(t1, t2)) {

        return stree_equals(t1->c, t2->c) && stree_equals(t1->s, t2->s);

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


void stree_destroy(STree st)
{
    if (st) {
        if (st->c) {
            stree_destroy(st->c);
        }
        if (st->s) {
            stree_destroy(st->s);
        }
        label_destroy(st->l);
        free(st);
    }
}
