
#include "writer.h"


static void write_stree2(const char *x, char *acc, Vertex scan)
{
    strcat(acc, "[");

    while (scan) {

        /* char mark[64]; */
        /* vertex_mark(mark, scan, x); */

        char tmp[STRING_MAX_LEN];
        sprintf(tmp, "<%d,%d,%d>", scan->l->i, scan->l->j, scan->k);
        strcat(acc, tmp);
        /* if (scan->k != -1) { */
        /*     sprintf(tmp, "%d", scan->k); */
        /*     strcat(acc, tmp); */
        /* } */
        write_stree2(x, acc, scan->c);
        char *end = scan->s ? "]," : "]";
        strcat(acc, end);
        scan = scan->s;
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

