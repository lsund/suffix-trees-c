
#include "reader.h"

int read_edge(const int o, const char *s, Edge *e)
{

    int i, k;

    i = 0;
    k = -1;

    while (s[i + o] != '[' && !isdigit(s[i + o]))
    {
        i++;
    }

    if (isdigit(s[i + o])) {
        k = char_to_int(s[i + o]);
    }

    *e = edge(s, o, o + i);
    (*e)->k = k;

    return k == -1 ? o + i + 1 : o + i + 2;
}

void read(const char *s, STree *tree)
{
    Edge e, ep, es, prev;
    int o;

    o     = read_edge(0, s, &e);
    e->k  = 1;
    ep    = e;
    *tree = e;

    prev = e;

    while (s[o]) {


        if (s[o] != ']') {

            o = read_edge(o, s, &e);
            stree_extend_edge_below(ep, e);
            prev = ep;
            ep = e;

        } else if (s[o + 1] == ',') {

            o = read_edge(o += 2, s, &es);
            stree_extend_edge_sibling(ep, es);
            ep = es;

        } else {
            ep = prev;
            o++;
        }

    }
}
