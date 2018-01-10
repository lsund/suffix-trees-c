
#include "ukkonen.h"


static void extend_end(TreeMatching tm, const char a)
{
    if (!stree_child_with(tm.end, a)) {
        label_extend(tm.end->lbl);
    }
}


static void split_end(TreeMatching tm, const char a, int i)
{
    stree_split(tm);
    stree_extend_edge_right(tm.end->child, edge_new_leaf(a, i));
}


STree ukkonen_naive(const char *text) {

    size_t len = strlen(text);
    STree tree = stree_init(text);
    char *mark = malloc(sizeof(char) * 128);

    for (unsigned long i = 1; i <= len - 1; i++) {

        char a = text[i];

        for(unsigned long j = 0; j <= i; j++) {

            /* sstring(mark, j, i - j, text); */
            LabelPointer lbl = label(text, j, i);

            TreeMatching tm = stree_find(tree, lbl);
            free(lbl);

            if (tm.m.size) {

                if (match_type(tm.m) == EXACT) {
                    extend_end(tm, a);
                } else {
                    if (label_char_at(tm.end->lbl, tm.m.size) != a) {
                        split_end(tm, a, j);
                    }
                }

            } else if (!stree_sibling_with(tree, a)) {
                stree_extend_edge_right(tree, edge_new_leaf(a, j));
            }
        }
    }
    free(mark);
    STree r = edge_from_string("R");
    stree_extend_edge_below(r, tree);
    return r;
}


