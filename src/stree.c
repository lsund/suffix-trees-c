#include "stree.h"

///////////////////////////////////////////////////////////////////////////////
// Edge


EdgePointer edge_from_mark(char *mark)
{
    EdgePointer ret;
    Label lbl = label(mark);
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


const char *edge_str(const EdgePointer e)
{
    return e->lbl->mark;
}


Matching edge_match_marking(EdgePointer e, const char *m)
{
    char *em = e->lbl->mark;
    unsigned long i, m_len, em_len, max_len;

    i = 0;
    m_len = strlen(m);
    em_len= strlen(em);
    max_len = m_len > em_len ? m_len : em_len;

    while (i < max_len && m[i] == em[i]) {
        i++;
    }
    int match       = i == em_len;
    int exact_match = match && em_len == m_len;

    Matching ret;

    if (exact_match) {

        ret.match = m;
        ret.rest  = NULL;

    } else if (match) {

        char *match = malloc(sizeof(char) * 128);
        char *rest = malloc(sizeof(char) * 128);
        sstring(m, 0, i, match);
        sstring(m, i, strlen(m) - i, rest);
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


EdgePointer stree_find(Stree tree, const char *m)
{
    Matching match = edge_match_marking(tree, m);

    switch (match_type(match)) {
        case NONE:
            return NULL;
            break;
        case PARTIAL:
            if (strcmp(m, match.match) == 0) {
                return tree;
            }
            if (tree->child) {

                EdgePointer probe = tree->child;

                while (probe) {

                    EdgePointer res = stree_find(probe, match.rest);
                    if (res) {
                        return res;
                    } else{
                        probe = probe->right;
                    }

                }
            }
            break;
        case EXACT:
            return tree;
    }

    return 0;
}


EdgePointer stree_init(const char *t)
{
    char *mark = malloc(sizeof(char) * STRING_INIT_LEN);
    sprintf(mark, "%c", t[0]);
    Label l =label(mark);

    EdgePointer ret = edge_from_label(l);

    return ret;
}


void stree_extend(Stree base, const EdgePointer ext)
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


void stree_extend_right(Stree base, const EdgePointer ext)
{
    EdgePointer probe = base;
    while (probe->right) {
        probe = probe->right;
    }
    probe->right = ext;
}
