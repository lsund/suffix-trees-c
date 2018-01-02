
#include "ukkonen.h"


static void extend_end(TreeMatching tm, const char a)
{
    if (!stree_child_with(tm.end, a)) {
        label_extend_letter(tm.end->lbl, a);
    }
}


static void split_end(TreeMatching tm, const char a)
{
    size_t k = strlen(tm.m.match);
    int next_character_matches = tm.end->lbl->mark[k] == a;

    if (!next_character_matches) {
        edge_split(tm.end, tm.m.match);
        stree_extend_edge_right( tm.end->child, edge_from_letter(a));
    }
}


STree ukkonen_naive(const char *text) {

    size_t len = strlen(text);
    STree tree = stree_init(text);
    char marking[128];

    for (unsigned long i = 1; i <= len - 1; i++) {

        char a = text[i];

        for(unsigned long j = 0; j <= i; j++) {

            sstring(marking, j, i - j, text);

            TreeMatching tm = stree_find(tree, marking);

            if (tm.m.match) {
                if (match_type(tm.m) == EXACT) {
                    extend_end(tm, a);
                } else {
                    split_end(tm, a);
                }
            } else {
                if (!stree_sibling_with(tree, a)) {
                    stree_extend_edge_right(tree, edge_from_letter(a));
                }
            }
        }
    }
    return tree;
}


