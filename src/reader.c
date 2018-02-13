
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
    Edge e, base, es;
    int o;

    o     = read_edge(0, s, &e);
    e->k  = 1;
    base  = e;
    *tree = e;

    while (s[o]) {


        if (s[o] != ']') {

            o = read_edge(o, s, &e);
            stree_extend_edge_below(base, e);
            base = e;

        } else if (s[o + 1] == ',') {

            o = read_edge(o += 2, s, &es);
            stree_extend_edge_sibling(base, es);
            base = es;

        } else if (s[o] == ']') {

            base = base->p;
            o++;

        } else {

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
