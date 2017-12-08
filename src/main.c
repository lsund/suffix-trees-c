
#include "suffix_tree.h"

void traverse_aux(EdgePointer probe)
{
    printf("[");
    while (probe) {
        edge_print(probe);
        traverse_aux(probe->child);
        if (probe->right) {
            printf("],");
        } else {
            printf("]");
        }
        probe = probe->right;
    }
}

void traverse(EdgePointer e)
{
    edge_print(e);
    EdgePointer probe = e;
    traverse_aux(probe->child);
    printf("]");
    printf("\n");
}


int main()
{
    char *text = "xaxa";
    EdgePointer i1 = stree_init(text);
    EdgePointer a1 = edge_from_mark("a", 1);
    EdgePointer b1 = edge_from_mark("b", 1);
    EdgePointer c1 = edge_from_mark("c", 1);
    EdgePointer b2 = edge_from_mark("b", 1);
    EdgePointer c2 = edge_from_mark("c", 1);
    EdgePointer c3 = edge_from_mark("c", 1);

    add_edge(i1, a1);
    add_edge(i1, b1);
    add_edge(i1, c1);
    add_edge(a1, b2);
    add_edge(b2, c3);
    add_edge(b1, c2);
    traverse(i1);

    return 0;
}
