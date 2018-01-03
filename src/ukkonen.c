
#include "ukkonen.h"


static void extend_end(TreeMatching tm, const char a)
{
    if (!stree_child_with(tm.end, a)) {

        label_extend(tm.end->lbl, a);
    }
}


static void split_end(TreeMatching tm, const char a)
{
    int next_character_matches = tm.end->lbl->mark[tm.m.size] == a;

    if (!next_character_matches) {
        edge_split(tm);
        stree_extend_edge_right( tm.end->child, edge_from_letter(a));
    }
}


STree ukkonen_naive(const char *text) {

    size_t len = strlen(text);
    STree tree = stree_init(text);
    char *mark = malloc(sizeof(char) * 128);

    for (unsigned long i = 1; i <= len - 1; i++) {

        char a = text[i];

        for(unsigned long j = 0; j <= i; j++) {

            sstring(mark, j, i - j, text);
            LabelPointer lbl = label(mark);

            TreeMatching tm = stree_find(tree, lbl);

            if (tm.m.size) {

                if (match_type(tm.m) == EXACT) {
                    extend_end(tm, a);
                } else {
                    split_end(tm, a);
                }
            } else if (!stree_sibling_with(tree, a)) {
                stree_extend_edge_right(tree, edge_from_letter(a));
            }
        }
    }
    free(mark);
    return tree;
}


