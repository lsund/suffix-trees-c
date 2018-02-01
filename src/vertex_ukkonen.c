
#include "vertex_ukkonen.h"


static void extend_end(const char *x, const Vertex v, const char a)
{
    if (!vertex_branches_with(x, v, a)) {
        label_extend_right2(v->l);
    }
}


/* static void split_end(TreeMatching2 tm, int k, Label l) */
/* { */
/*     stree_split(tm); */
/*     Edge new_leaf = edge_leaf(l->s, l->i + tm.m.n, l->i + tm.m.n + 1, k); */
/*     stree_extend_edge_sibling(tm.end->c, new_leaf); */
/* } */


/* STree ukkonen_naive(const char *text) { */

/*     size_t len = strlen(text); */
/*     STree2 tree = stree_init2(text); */

/*     for (unsigned long i = 1; i <= len - 1; i++) { */

/*         char a = text[i]; */

/*         for(unsigned long j = 0; j <= i; j++) { */

/*             Label2 l = label2(j, i); */

/*             TreeMatching2 tm = scan_prefix2(tree, l); */

/*             if (tm.m.n) { */

/*                 if (match_type(tm.m) == EXACT) { */
/*                     extend_end(text, tm.end, a); */
/*                 } else { */
/*                     char last = label_char_at_2(text, tm.end->l, tm.m.n); */
/*                     if (last != a) { */
/*                         split_end(tm, j, l); */
/*                     } */
/*                 } */

/*             } else if (!stree_sibling_with(tree, a)) { */
/*                 stree_extend_edge_sibling(tree, edge_leaf(text, j, j + 1, j)); */
/*             } */
/*             free(l); */
/*         } */
/*     } */
/*     STree r = edge("R", 0, 1); */
/*     stree_extend_edge_below(r, tree); */
/*     return r; */
/* } */
