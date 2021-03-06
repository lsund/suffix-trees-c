#include "matching.h"

Matching matching_empty()
{
    Matching m;
    m.n  = 0;
    m.l  = 0;
    m.r = 0;

    return m;
}

MatchType match_type(const Matching m)
{
    MatchType partial = m.l ? PARTIAL_LEFT : PARTIAL_RIGHT;

    if (m.n) {
        return !m.l && !m.r ? EXACT : partial;
    } else {
        return m.l && m.r ? NONE : partial;
    }
}


Matching match(const Label l1, const Label l2)
{

    Matching m;
    int min, n2, n1;
    char lc, rc;

    m.n = 0;
    n1 = l1->j - l1->i;
    n2 = l2->j - l2->i;
    min  = n2 > n1 ? n1 : n2;

    while  (m.n < min) {

        rc = label_char_at(l2, m.n);
        lc = label_char_at(l1, m.n);

        if (rc != lc) {
            break;
        } else {
            m.n++;
        }

    }

    m.l  = n1 - m.n;
    m.r = n2 - m.n;

    return m;
}

Matching match2(const char *x, const Vertex v, const Label2 l)
{
    Matching m;
    int min, nl, nv;
    char lc, rc;

    m.n = 0;
    nv = v->l->j - v->l->i;
    nl = l->j - l->i;
    min  = nl > nv ? nv : nl;

    while  (m.n < min) {

        lc = vertex_char_at(x, v, m.n);
        rc = label_char_at_2(x, l, m.n);

        if (rc != lc) {
            break;
        } else {
            m.n++;
        }

    }

    m.l  = nv - m.n;
    m.r = nl - m.n;

    return m;
}
