
#include "writer.h"


static void write_stree2(const char *x, char *acc, Vertex scan)
{
    strcat(acc, "[");

    while (scan) {

        char mark[64];
        vertex_mark(mark, scan, x);

        strcat(acc, mark);
        printf("%d\n", scan->k);
        if (scan->k != -1) {
            char tmp[STRING_MAX_LEN];
            sprintf(tmp, "%d", scan->k);
            strcat(acc, tmp);
        }
        write_stree2(x, acc, scan->c);
        char *end = scan->s ? "]," : "]";
        strcat(acc, end);
        scan = scan->s;
    }
}

static void write_stree(char *acc, Edge probe)
{
    strcat(acc, "[");

    while (probe) {

        char mark[64];
        edge_mark(probe, mark);

        strcat(acc, mark);
        if (probe->k != -1) {
            char tmp[STRING_MAX_LEN];
            sprintf(tmp, "%d", probe->k);
            strcat(acc, tmp);
        }
        write_stree(acc, probe->c);
        char *end = probe->s ? "]," : "]";
        strcat(acc, end);
        probe = probe->s;
    }
}

void write2(char *acc, const STree2 tree)
{

    Vertex scan = tree->r;

    char mark[64];
    vertex_mark(mark, scan, tree->x);
    strcat(acc, mark);

    if (scan->k != -1) {
        sprintf(acc, "%s%d", acc, scan->k);
    }
    write_stree2(tree->x, acc, scan->c);
    strcat(acc, "]");
}

void write(char *s, const STree tree)
{

    Edge probe = tree;

    char mark[64];
    edge_mark(probe, mark);
    strcat(s, mark);

    if (probe->k != -1) {
        sprintf(s, "%s%d", s, probe->k);
    }
    write_stree(s, probe->c);
    strcat(s, "]");
}


void write_file(const char *path, const STree tree)
{
    char *res = calloc(256, sizeof(char));
    write(res, tree);

    FILE *f = fopen(path, "w");
    if (f) {
        fprintf(f, "%s\n", res);
    } else {
        printf("Could not open file.\n");
    }
    fclose(f);
    free(res);
}


