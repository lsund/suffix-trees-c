
#include "writer.h"

static void write_stree(EdgePointer probe, char *acc)
{
    strcat(acc, "[");

    while (probe) {

        char mark[64];
        edge_mark(probe, mark);

        strcat(acc, mark);
        if (probe->leaf_number != -1) {
            sprintf(acc, "%s%d", acc, probe->leaf_number);
        }
        write_stree(probe->child, acc);
        char *end = probe->right ? "]," : "]";
        strcat(acc, end);
        probe = probe->right;
    }
}

void write(const STree tree, char *s)
{

    EdgePointer probe = tree;

    char mark[64];
    edge_mark(probe, mark);
    strcat(s, mark);

    if (probe->leaf_number != -1) {
        sprintf(s, "%s%d", s, probe->leaf_number);
    }
    write_stree(probe->child, s);
    strcat(s, "]");
}


void write_file(const STree tree, const char *path)
{
    char *res = calloc(256, sizeof(char));
    write(tree, res);

    FILE *f = fopen(path, "w");
    if (f) {
        fprintf(f, "%s\n", res);
    } else {
        printf("Could not open file.\n");
    }
    fclose(f);
    free(res);
}


