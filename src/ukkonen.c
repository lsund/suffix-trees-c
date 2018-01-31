
#include "ukkonen.h"


static void extend_end(TreeMatching tm, const char a)
{
    if (!stree_child_with(tm.end, a)) {
        label_extend(tm.end->l);
    }
}


static void split_end(TreeMatching tm, int k, Label l)
{
    stree_split(tm);
    Edge new_leaf = edge_leaf(l->s, l->i + tm.m.n, l->i + tm.m.n + 1, k);
    stree_extend_edge_sibling(tm.end->c, new_leaf);
}


STree ukkonen_naive(const char *text) {

    size_t len = strlen(text);
    STree tree = stree_init(text);
    STree2 tree2 = stree_init2(text);

    for (unsigned long i = 1; i <= len - 1; i++) {

        char a = text[i];

        for(unsigned long j = 0; j <= i; j++) {

            Label l = label(text, j, i);
            TreeMatching tm = scan_prefix(tree, l);

            if (tm.m.n) {

                // Check that matching works
                if (match_type(tm.m) == EXACT) {
                    extend_end(tm, a);
                } else {
                    char last = label_char_at(tm.end->l, tm.m.n);
                    if (last != a) {
                        split_end(tm, j, l);
                    }
                }

            } else if (!stree_sibling_with(tree, a)) {
                stree_extend_edge_sibling(tree, edge_leaf(text, j, j + 1, j));
            }
            free(l);
        }
    }
    STree r = edge("R", 0, 1);
    stree_extend_edge_below(r, tree);
    return r;
}


