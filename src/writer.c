
#include "writer.h"

static void write_stree(EdgePointer probe, char *acc)
{
    strcat(acc, "[");

    while (probe) {

        const char *mark = edge_str(probe);
        int i = probe->lbl->i;
        int n = probe->lbl->j;
        char buf[n - i + 2];
        memcpy(buf, &mark[i], n);
        buf[n] = '\0';

        strcat(acc, buf);
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
    strcat(s, edge_str(tree));
    write_stree(probe->child, s);
    if (probe->leaf_number != -1) {
        sprintf(s, "%s%d", s, probe->leaf_number);
    }
    strcat(s, "]");
}


void write_file(const STree tree, const char *path)
{
    char *res = malloc(sizeof(char) * 256);
    *res = '\0';
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


