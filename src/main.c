
#include "suffix_tree.h"

void traverse_aux(EdgePointer probe)
{
    printf("[");
    while (probe) {
        printf("(%s)", probe->lbl.mark);
        traverse_aux(probe->child);
        probe = probe->right;
    }
    printf("]");
}

void traverse(EdgePointer e)
{
    EdgePointer probe = e;
    traverse_aux(probe);
    printf("\n");
}


int main()
{
    char *text = "xaxa";
    EdgePointer i1 = stree_init(text);
    EdgePointer a = edge_from_mark("a", 1);
    EdgePointer b = edge_from_mark("b", 1);
    EdgePointer c = edge_from_mark("c", 1);
    EdgePointer d = edge_from_mark("d", 1);

    add_edge(i1, a);
    add_edge(i1, b);
    add_edge(a, c);
    add_edge(a, d);
    traverse(i1);

    return 0;
}
