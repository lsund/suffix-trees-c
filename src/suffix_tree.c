#include "suffix_tree.h"

// TODO Find out a good way of printing these trees. Use haskell pretty-print?

// Construct tree I1
// for i from 1 to m - 1 do
//      begin phase i + 1
//      for j from 1 to i + 1
//          begin extension j
//          find the end of the path from the root labaled S[j..i] in the
//          current tree. If needed, extend that path by adding acharacter
//          S(i+1)
//      end
// end


void edge_print(EdgePointer e)
{
    printf("%s", e->lbl.mark);
}


Label label(char *mark, size_t len)
{
    Label ret;
    ret.mark = mark;
    ret.len = len;
    return ret;
}


EdgePointer edge_from_mark(char *mark, size_t len)
{
    EdgePointer ret;
    Label lbl = label(mark, len);
    ret = malloc(sizeof(Edge));
    ret->lbl = lbl;
    ret->child = NULL;

    return ret;
}


EdgePointer edge_from_label(Label lbl)
{
    EdgePointer ret;
    ret = malloc(sizeof(Edge));
    ret->lbl = lbl;
    ret->child = NULL;

    return ret;
}


void add_edge(EdgePointer base, EdgePointer ext)
{
    if (!base->child) {
        base->child = ext;
    } else {
        EdgePointer probe = base->child;
        while (probe->right) {
            probe = probe->right;
        }
        probe->right = ext;
    }
}


EdgePointer stree_init(char *t)
{
    char *mark = malloc(sizeof(char) * 2);
    sprintf(mark, "%c", t[0]);
    Label l =label(mark, 2);

    EdgePointer ret = edge_from_label(l);

    return ret;
}
