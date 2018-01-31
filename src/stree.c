#include "stree.h"


STree stree_init(const char *s)
{
    return edge_leaf(s, 0, 1, 0);
}


STree2 stree_init2(const char *x)
{
    STree2 ret = malloc(sizeof(STree2));
    ret->r = vertex(-1, -1);
    ret->x    = x;
    return ret;
}

TreeMatching2 scan_prefix2_aux(const char *x, Vertex v, const Label2 pre)
{
    Label2 rl = vertex_label_below(v);
    Matching m = match2(x, rl, pre);

    TreeMatching2 ret;
    ret.m = matching_empty();
    ret.end = NULL;

    switch (match_type(m)) {
        case NONE:
            if (v->s) {
                return scan_prefix2_aux(x, v->s, pre);
            }
        case PARTIAL_RIGHT:
            // The whole mark of the tree label was matched, but something
            // in c is left. Try to continue with ec nodes.
            if (v->c) {
                label_shrink_left2(pre, m.n);
                return scan_prefix2_aux(x, v->c, pre);
            } else {
                return ret;
            }
        case PARTIAL_LEFT:
            // The whole c was matched but ended up in the middle of the tree
            // label.
            ret.m = m;
            ret.end = v;
            return ret;
        case EXACT:
            ret.m = m;
            ret.end = v;
            return ret;
    }

    return ret;
}

TreeMatching2 scan_prefix2(STree2 tree, const Label2 pre)
{
    return scan_prefix2_aux(tree->x, tree->r, pre);
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
        ext->p = st;

    } else {

        Edge scan = st->c;
        while (scan->s) {
            scan = scan->s;
        }

        scan->s = ext;
        ext->p = st;

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
    ext->p = st->p;
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
