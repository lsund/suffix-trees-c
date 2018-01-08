
#include "reader.h"

int read_edge(const int o, const char *s, EdgePointer *e)
{
    int i = 0;
    while (s[i + o] != '[')
    {
        i++;
    }

    int leaf_number = -1;
    if (isdigit(s[o + 2])) {
        leaf_number = char_to_int(s[o + 2]);
    }

    char *lbl = malloc(sizeof(char) * STRING_INIT_LEN);
    sstring(lbl, o, i, s);
    *e = edge_from_string(lbl);
    (*e)->leaf_number = leaf_number;

    return o + i + 1;
}

void read(const char *s, STree *tree)
{
    EdgePointer e, parent, sibling;
    int o = read_edge(0, s, &e);
    e->leaf_number = 1;
    parent = e;
    *tree = e;
    while (s[o]) {
        if (!isdigit(s[o])) {
            o = read_edge(o, s, &e);
            stree_extend_edge_below(parent, e);
            parent = e;
        } else if (s[o + 2] == ',') {
            o = read_edge(o += 3, s, &sibling);
            stree_extend_edge_right(parent, sibling);
            parent = sibling;
        } else {
            break;
        }
    }
}
