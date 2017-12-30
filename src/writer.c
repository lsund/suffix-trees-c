
#include "writer.h"

static void write_stree_aux(EdgePointer probe, char *acc)
{
    strcat(acc, "[");
    while (probe) {
        strcat(acc, edge_str(probe));
        write_stree_aux(probe->child, acc);
        if (probe->right) {
            strcat(acc, "],");
        } else {
            strcat(acc, "]");
        }
        probe = probe->right;
    }
}

static void write_stree(const STree tree, char *acc)
{
    EdgePointer probe = tree;
    strcat(acc, edge_str(probe));
    write_stree_aux(probe->child, acc);
    strcat(acc, "]");
}


void write_stree_to_file(const STree tree, const char *path)
{
    char *res = malloc(sizeof(char) * 128);
    write_stree(tree, res);

    FILE *f = fopen(path, "w");
    if (f) {
        fprintf(f, "%s\n", res);
    } else {
        printf("Could not open file.\n");
    }
    free(res);
}


