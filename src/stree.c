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
            if (tree->es) {
                return stree_find(tree->es, l);
            } else {
                return ret;
            }
        case PARTIAL_RIGHT:
            // The whole mark of the tree label was matched, but something
            // in c is left. Try to continue with ec nodes.
            if (tree->ec) {
                label_shrink_left(l, m.n);
                return stree_find(tree->ec, l);
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


int stree_es_with(STree tree, char c)
{
    if (!tree) return 1;

    Edge probe = tree;

    while(probe) {
        if (label_char_at(probe->l, 0) == c) {
            return 1;
        }
        probe = probe->es;
    }
    return 0;
}


int stree_child_with(STree tree, char c)
{
    Edge probe = tree->ec;
    while(probe) {
        if (label_char_at(probe->l, 0) == c) {
            return 1;
        }
        probe = probe->es;
    }
    return 0;
}


void stree_extend_edge_below(STree tree, const Edge ext)
{
    int tmp = tree->k;
    if (!tree->ec) {
        tree->ec = ext;
    } else {
        Edge probe = tree->ec;
        while (probe->es) {
            probe = probe->es;
        }
        probe->es = ext;
    }
    tree->k = -1;
    if (ext->k == -1) {
        ext->k = tmp;
    }
}


void stree_extend_edge_sibling(STree tree, const Edge ext)
{
    Edge probe = tree;

    while (probe->es) {
        probe = probe->es;
    }

    probe->es = ext;
}


void stree_split(TreeMatching tm)
{
    int j = tm.end->l->j;
    label_set_right(tm.end->l, tm.m.n + tm.end->l->i);

    Edge ec = edge(tm.end->l->s, tm.m.n + tm.end->l->i, j);

    stree_extend_edge_below(tm.end, ec);
}


void stree_permute(STree tree, int i)
{
    int n = 0;

    Edge siblings[64];
    Edge probe = tree->ec;
    while (probe) {
        siblings[n] = probe;
        probe = probe->es;
        n++;
    }
    /* probe = tree->ec; */
    /* while (probe) { */
    /*     label_print(probe->l); */
    /*     probe = probe->es; */
    /* } */

    char s[1000];
    char p[64];

    char *set = "01";
    strcpy(s, set);

    nth_permutation(i, s, p);

    size_t j;
    int order[64];
    for (j = 0; j < strlen(set); j++)
    {
        order[j] = char_to_int(p[j]);
    }

    /* for (j = 0; j < strlen(set) - 1; j++) */
    /* { */
    /*     printf("order[%zu]: %d order[%zu]: %d\n", j, order[j], j + 1, order[j + 1]); */
    /* } */

    for (j = 0; j < strlen(set) - 1; j++)
    {
        siblings[order[j]]->es = siblings[order[j] + 1];
    }
    siblings[order[strlen(set) - 1]]->es = NULL;
    tree->ec = siblings[order[0]];



}


void stree_destroy(STree tree)
{
    if (tree) {
        if (tree->ec) {
            stree_destroy(tree->ec);
        }
        if (tree->es) {
            stree_destroy(tree->es);
        }
        label_destroy(tree->l);
        free(tree);
    }
}
