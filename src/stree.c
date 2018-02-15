#include "stree.h"


STree2 stree_init2(const char *x)
{
    STree2 ret = malloc(sizeof(STree2));
    ret->r     = vertex_root();
    ret->x     = x;
    return ret;
}

TreeMatching2 scan_prefix2_aux(const char *x, Vertex v, const Label2 pre)
{
    TreeMatching2 ret;
    ret.m = matching_empty();
    ret.end = NULL;

    Matching m = match2(x, v, pre);

    if (vertex_is_root(v)) {
        if (v->c) {
            return scan_prefix2_aux(x, v->c, pre);
        } else {
            ret.m = m;
            ret.end = v;
            return ret;
        }
    }


    switch (match_type(m)) {
        case NONE:
            if (v->s) {
                return scan_prefix2_aux(x, v->s, pre);
            } else {
                return ret;
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




void stree_extend_right(STree2 st, const Vertex v)
{
    vertex_extend_right(st->r, v);
}


void stree_split2(TreeMatching2 tm)
{
    int i = tm.end->l->i;
    int j = tm.end->l->j;

    int new_right = tm.m.n + i;

    label_set_right2(tm.end->l, new_right);

    Vertex c = vertex(new_right, j);

    vertex_extend_below(tm.end, c);
}


void stree_mark(char *t, STree2 st, Vertex v)
{
    vertex_mark(t, v, st->x);
}
