
#include "ukkonen.h"


static void extend_end(TreeMatching tm, const char a)
{
    if (!stree_child_with(tm.end, a)) {
        label_extend(tm.end->lbl);
    }
}


static void split_end(TreeMatching tm, int k, LabelPointer lbl)
{
    stree_split(tm);
    EdgePointer new_leaf = edge_leaf(lbl->text, lbl->i + tm.m.size, lbl->i + tm.m.size + 1, k);
    stree_extend_edge_right(tm.end->child, new_leaf);
}


STree ukkonen_naive(const char *text) {

    size_t len = strlen(text);
    STree tree = stree_init(text);
    char *mark = malloc(sizeof(char) * 128);

    for (unsigned long i = 1; i <= len - 1; i++) {

        char a = text[i];

        for(unsigned long j = 0; j <= i; j++) {

            LabelPointer lbl = label(text, j, i);

            TreeMatching tm = stree_find(tree, lbl);

            if (tm.m.size) {

                // Check that matching works
                if (match_type(tm.m) == EXACT) {
                    extend_end(tm, a);
                } else {
                    char last = label_char_at(tm.end->lbl, tm.m.size);
                    if (last != a) {
                        split_end(tm, j, lbl);
                    }
                }

            } else if (!stree_sibling_with(tree, a)) {
                stree_extend_edge_right(tree, edge_leaf(text, j, j + 1, j));
            }
        }
    }
    free(mark);
    STree r = edge_from_string("R");
    stree_extend_edge_below(r, tree);
    return r;
}


