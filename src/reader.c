
#include "reader.h"

int read_vertex(const int o, const char *rep, Vertex *v)
{

    int p, k;

    int i, j;

    p = 0;
    k = -1;


    if (rep[p + o] == 'r') {
        *v = vertex_root();
        return 1;
    }

    i = char_to_int(rep[p + o]);
    p++;
    p++;
    j = char_to_int(rep[p + o]);
    p++;
    p++;
    if (rep[p + o] == '-') {
        p++;
        k = -char_to_int(rep[p + o]);
    } else {
        k = char_to_int(rep[p + o]);
    }
    p++;
    *v = vertex_leaf(i, j, k);

    return p + o;

}

void read2(const char *rep, STree2 tree)
{
    Vertex v, base, vs;
    int o;

    o     = read_vertex(0, rep, &v);
    v->k  = 1;
    base  = v;
    tree->r = v;

    while (rep[o]) {

        if (rep[o] == '[') {
            if (rep[o + 1] == ']') {
                o += 2;
            } else {
                o = o + 2;
                o = read_vertex(o, rep, &v);
                vertex_extend_below(base, v);
                base = v;
                o++;
            }
        } else if (rep[o] == ',') {
            o = o + 2;
            o = read_vertex(o, rep, &vs);
            vertex_extend_right(base, vs);
            base = vs;
        } else {
            if (rep[o] == ']') {
                base = base->p;
            }
            o++;
        }
    }
}


void rep_to_string(char *x, const char *rep)
{
    int i = 1;
    int j = 0;
    while (rep[i]) {
        if (rep[i] == ']') {
            break;
        }
        if (isalpha(rep[i])) {
            x[j] = rep[i];
            j++;
        }
        i++;
    }
    x[j] = '\0';
}
