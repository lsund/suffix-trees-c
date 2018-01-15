
#include "reader.h"

int read_edge(const int o, const char *s, Edge *e)
{
    int i = 0;
    while (s[i + o] != '[' && !isdigit(s[i + o]))
    {
        i++;
    }

    int leaf_number = -1;
    if (isdigit(s[i + o])) {
        leaf_number = char_to_int(s[i + o]);
    }
    Edge new_edge = edge(s, o, o + i);

    *e = new_edge;
    (*e)->leaf_number = leaf_number;

    return leaf_number == -1 ? o + i + 1 : o + i + 2;
}

void read(const char *s, STree *tree)
{
    Edge e, parent, sibling;
    int o = read_edge(0, s, &e);
    e->leaf_number = 1;
    parent = e;
    *tree = e;
    while (s[o]) {
        if (s[o] != ']') {
            o = read_edge(o, s, &e);
            stree_extend_edge_below(parent, e);
            parent = e;
        } else if (s[o + 1] == ',') {
            o = read_edge(o += 2, s, &sibling);
            stree_extend_edge_sibling(parent, sibling);
            parent = sibling;
        } else {
            break;
        }
    }
}
