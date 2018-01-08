
#include "writer.h"

static void write_stree_aux(EdgePointer probe, char *acc)
{
    strcat(acc, "[");
    while (probe) {

        const char *mark = edge_str(probe);
        int i = probe->lbl->i;
        int n = probe->lbl->n;
        char buf[n - i + 2];
        memcpy(buf, &mark[i], n);
        buf[n] = '\0';

        strcat(acc, buf);
        write_stree_aux(probe->child, acc);
        if (probe->right) {
            strcat(acc, "],");
        } else {
            strcat(acc, "]");
        }
        probe = probe->right;
    }
}

void write(const STree tree, char *s)
{
    EdgePointer probe = tree;
    strcat(s, edge_str(tree));
    write_stree_aux(probe->child, s);
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


