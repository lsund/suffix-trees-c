
#include "writer.h"


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


