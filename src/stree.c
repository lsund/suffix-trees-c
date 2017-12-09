#include "stree.h"

///////////////////////////////////////////////////////////////////////////////
// Label


Label label(const char *mark, const size_t len)
{
    Label ret;
    ret.mark = mark;
    ret.len = len;
    return ret;
}


///////////////////////////////////////////////////////////////////////////////
// Edge


const char *edge_str(const EdgePointer e)
{
    return e->lbl.mark;
}


EdgePointer edge_from_mark(const char *mark, const size_t len)
{
    EdgePointer ret;
    Label lbl = label(mark, len);
    ret = malloc(sizeof(Edge));
    ret->lbl = lbl;
    ret->child = NULL;

    return ret;
}


EdgePointer edge_from_label(const Label lbl)
{
    EdgePointer ret;
    ret = malloc(sizeof(Edge));
    ret->lbl = lbl;
    ret->child = NULL;

    return ret;
}


///////////////////////////////////////////////////////////////////////////////
// Suffix Tree


EdgePointer stree_init(const char *t)
{
    char *mark = malloc(sizeof(char) * 2);
    sprintf(mark, "%c", t[0]);
    Label l =label(mark, 2);

    EdgePointer ret = edge_from_label(l);

    return ret;
}


void stree_extend(EdgePointer base, const EdgePointer ext)
{
    if (!base->child) {
        base->child = ext;
    } else {
        EdgePointer probe = base->child;
        while (probe->right) {
            probe = probe->right;
        }
        probe->right = ext;
    }
}
