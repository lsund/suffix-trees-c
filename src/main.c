
#include "suffix_tree.h"

void stree_to_text_aux(EdgePointer probe, char *acc)
{
    strcat(acc, "[");
    while (probe) {
        strcat(acc, edge_str(probe));
        stree_to_text_aux(probe->child, acc);
        if (probe->right) {
            strcat(acc, "],");
        } else {
            strcat(acc, "]");
        }
        probe = probe->right;
    }
}

void stree_to_text(EdgePointer e, char *acc)
{
    EdgePointer probe = e;
    strcat(acc, edge_str(probe));
    stree_to_text_aux(probe->child, acc);
    strcat(acc, "]");
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
    EdgePointer o1 = edge_from_mark("o", 1);

    add_edge(i1, a1);
    add_edge(i1, b1);
    add_edge(i1, c1);
    add_edge(a1, b2);
    add_edge(b2, c3);
    add_edge(b1, c2);
    add_edge(c1, o1);

    char *res = malloc(sizeof(char) * 128);
    stree_to_text(i1, res);

    FILE *f = fopen("../suffix-trees/data/sample", "w");
    if (f) {
        fprintf(f, "%s\n", res);
    } else {
        printf("Could not open file.\n");
    }
    free(res);
    return 0;
}
