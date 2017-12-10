#include "stree.h"

///////////////////////////////////////////////////////////////////////////////
// Label


Label label(char *mark, const size_t len)
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


EdgePointer edge_from_mark(char *mark, const size_t len)
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


Matching edge_match_marking(EdgePointer e, const char *m)
{
    char *em = e->lbl.mark;
    unsigned long i, m_len, em_len, max_len;

    i = 0;
    m_len = strlen(m);
    em_len= strlen(em);
    max_len = m_len > em_len ? m_len : em_len;

    while (i < max_len && m[i] == em[i]) {
        i++;
    }
    int match       = i == m_len;
    int exact_match = match && em_len == m_len;

    Matching ret;

    if (exact_match) {

        ret.match = m;
        ret.rest  = NULL;

    } else if (match) {

        char match[128];
        char rest[128];
        sstring(em, 0, i, match);
        sstring(em, i, strlen(em) - i, rest);
        ret.match = match;
        ret.rest  = rest;

    } else {

        ret.match = NULL;
        ret.rest  = NULL;

    }

    return ret;
}


///////////////////////////////////////////////////////////////////////////////
// Suffix Tree


EdgePointer stree_find(EdgePointer tree, const char *m)
{
    EdgePointer probe = tree;
    return NULL;
}


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
