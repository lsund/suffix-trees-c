
#include "vertex_ukkonen.h"


static void extend_end(const char *x, const Vertex v, const char a)
{
    if (!vertex_branches_with(x, v, a)) {
        label_extend_right2(v->l);
    }
}


static void split_end(TreeMatching2 tm, int k, Label2 l)
{
    stree_split2(tm);
    Vertex new_leaf = vertex_leaf(l->i + tm.m.n, l->i + tm.m.n + 1, k);
    vertex_extend_right(tm.end->c, new_leaf);
}


STree2 ukkonen_naive2(const char *text)
{

    int len = strlen(text);
    STree2 tree = stree_init2(text);

    for (int i = 0; i <= len - 1; i++) {

        char a = text[i];

        for(int j = 0; j <= i; j++) {

            Label2 l = label2(j, i + 1);

            /* label_print2(text, l); */

            /* printf("%d %d\n",j, i); */

            TreeMatching2 tm = scan_prefix2(tree, l);

            if (tm.m.n) {

                if (match_type(tm.m) == EXACT) {
                    extend_end(text, tm.end, a);
                } else {
                    char last = label_char_at_2(text, tm.end->l, tm.m.n);
                    if (last != a) {
                        split_end(tm, j, l);
                    }
                }

            } else if (!vertex_sibling_with(text, tree->r, a)) {
                vertex_extend_right(tree->r, vertex_leaf(j, j + 1, j));
            }
            free(l);
        }
    }
    return tree;
}
