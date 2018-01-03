
#include "ukkonen.h"


static void extend_end(TreeMatching tm, const char a)
{
    if (!stree_child_with(tm.end, a)) {

        label_extend(tm.end->lbl, a);
    }
}


static void split_end(TreeMatching tm, const char a)
{
    int next_character_matches = tm.end->lbl->mark[tm.m.match_both] == a;
    char *new = malloc(sizeof(char) * STRING_INIT_LEN);
    sstring(new, 0, tm.m.match_both, tm.end->lbl->mark);

    if (!next_character_matches) {
        edge_split(tm.end, new);
        stree_extend_edge_right( tm.end->child, edge_from_letter(a));
    }
}


STree ukkonen_naive(const char *text) {

    size_t len = strlen(text);
    STree tree = stree_init(text);
    char *marking = malloc(sizeof(char) * 128);

    for (unsigned long i = 1; i <= len - 1; i++) {

        char a = text[i];

        for(unsigned long j = 0; j <= i; j++) {

            sstring(marking, j, i - j, text);

            TreeMatching tm = stree_find(tree, marking);

            if (tm.m.match_both) {

                if (match_type(tm.m) == EXACT) {
                    extend_end(tm, a);
                } else {
                    split_end(tm, a);
                }
            } else if (!stree_sibling_with(tree, a)) {
                stree_extend_edge_right(tree, edge_from_letter(a));
            }

            treematching_destroy(tm);
        }
    }
    free(marking);
    return tree;
}


