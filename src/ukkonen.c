
#include "ukkonen.h"


static void extend_end(EdgePointer end, const char a)
{
    if (!stree_child_with(end, a)) {
        label_extend_letter(end->lbl, a);
    }
}


static void split_end(TreeMatching tm, const char a)
{
    size_t k = strlen(tm.m.match);
    int next_character_matches = tm.tree->lbl->mark[k] == a;

    if (!next_character_matches) {
        edge_split(tm.tree, tm.m.match);
        stree_extend_edge_right( tm.tree->child, edge_from_letter(a));
    }
}


STree ukkonen_naive() {

    char *text = "abaababa";
    size_t len = strlen(text);
    STree tree = stree_init(text);
    char t[8];

    for (unsigned long i = 1; i <= len - 1; i++) {
        for(unsigned long j = 0; j <= i; j++) {

            sstring(t, j, i - j, text);
            char a = text[i];

            TreeMatching tm = stree_find(tree, t);
            STree end = tm.tree;

            if (tm.m.match) {

                if (match_type(tm.m) == EXACT) {
                    extend_end(end, a);
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


