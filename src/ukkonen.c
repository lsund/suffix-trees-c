
#include "ukkonen.h"


static void extend_end(TreeMatching tm, const char a)
{
    if (!stree_child_with(tm.end, a)) {
        label_extend(tm.end->lbl);
    }
}


static void split_end(TreeMatching tm, int k)
{
    stree_split(tm);
    LabelPointer lbl = tm.end->lbl;
    stree_extend_edge_right(
            tm.end->child,
            edge_leaf(lbl->text, lbl->i, lbl->i + 2, k)
    );
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
            free(lbl);

            if (tm.m.size) {

                // Check that matching works
                if (match_type(tm.m) == EXACT) {
                    printf("Before\n");
                    label_print(tm.end->lbl);
                    extend_end(tm, a);
                    printf("After\n");
                    label_print(tm.end->lbl);
                } else {
                    char last = label_char_at(tm.end->lbl, tm.m.size);
                    if (last != a) {
                        split_end(tm, j);
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


