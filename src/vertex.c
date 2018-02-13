
#include "vertex.h"

int vertex_children_equals_aux(const char *x, Vertex v1, Vertex v2)
{
    if (v1 && v2 && label_equals(x, v1->l, v2->l)) {
        return vertex_children_equals_aux(x, v1->s, v2->s);
    } else {
        return !v1 && !v2;
    }
}


int vertex_children_equals(const char *x, Vertex v1, Vertex v2)
{
    return vertex_children_equals_aux(x, v1->c, v2->c);
}

int vertex_equals(const char *x, Vertex v1, Vertex v2)
{
    if (v1 && v2 && label_equals(x, v1->l, v2->l)) {

        return vertex_equals(x, v1->c, v2->c) && vertex_equals(x, v1->s, v2->s);

    } else {
        return !v1 && !v2;
    }
}


Vertex vertex_root()
{
    return vertex_leaf(-1, -1, 0);
}


Vertex vertex(const int i, const int j)
{
    return vertex_leaf(i, j, -1);
}


Vertex vertex_leaf(const int i, const int j, const int k)
{
    Vertex v;
    v = malloc(sizeof(struct vertex));
    v->l = label2(i, j);
    v->k = k;
    v->c = NULL;
    v->s = NULL;
    v->p = NULL;

    return v;
}


int vertex_is_root(const Vertex v)
{
    return label_is_undefined(v->l);
}


int vertex_n_siblings(const Vertex v)
{
    int n = 0;
    Vertex scan = v->c;
    while (scan) {
        scan = scan->s;
        n++;
    }
    return n;
}


void vertex_extend_below(Vertex v, const Vertex c)
{
    int tmp = v->k;

    if (!v->c) {

        v->c = c;
        c->p = v;

    } else {

        Vertex scan = v->c;
        while (scan->s) {
            scan = scan->s;
        }

        scan->s = c;
        c->p = v;

    }

    v->k = -1;

    if (c->k == -1) {
        c->k = tmp;
    }

}


void vertex_extend_right(Vertex v, Vertex s)
{

    Vertex scan = v;

    while (scan->s) {
        scan = scan->s;
    }

    scan->s = s;
    s->p = v->p;

}


void vertex_mark(char *t, Vertex v, const char *x)
{
    if (vertex_is_root(v)) {
        strcpy(t, "r");
    } else {
        label_mark2(t, v->l, x);
    }
}


char vertex_char_at(const char *x, Vertex v, int i)
{
    return label_char_at_2(x, v->l, i);
}


void vertex_destroy(Vertex v)
{
    free(v);
}


int vertex_branches_with(const char *x, const Vertex v, const char c)
{
    Vertex scan = v->c;
    while(scan) {
        if (label_char_at_2(x, scan->l, 0) == c) {
            return 1;
        }
        scan = scan->s;
    }
    return 0;
}


int vertex_sibling_with(const char *x, const Vertex v, const char c)
{
    if (!v) return 1;

    Vertex scan = v;

    while(scan) {
        if (label_char_at_2(x, scan->l, 0) == c) {
            return 1;
        }
        scan = scan->s;
    }
    return 0;
}

void vertex_permute(Vertex v, int i)
{
    int j;
    int n = 0;
    int ord[64];
    char seq[STRING_MAX_LEN];
    char perm[STRING_MAX_LEN];
    Vertex siblings[MAX_BRANCHING], scan;

    scan = v->c;
    while (scan) {
        siblings[n] = scan;
        scan = scan->s;
        n++;
    }
    if (!n) {
        return;
    }
    if (i > factorial(n) - 1) {
        runtime_error("stree_permute: permutation index too damn high!");
        return;
    }

    nat_sequence(seq, n);
    nth_permutation(perm, i, seq);

    for (j = 0; j < n; j++) {
        ord[j] = char_to_int(perm[j]);
    }

    v->c = siblings[ord[0]];

    for (j = 0; j < n - 1; j++) {
        siblings[ord[j]]->s = siblings[ord[j + 1]];
    }

    siblings[ord[n - 1]]->s = NULL;

}


void vertex_permute_inverse(Vertex v, int i)
{
    int n = vertex_n_siblings(v);
    vertex_permute(v, permutation_inverse_number(i, n));
}



int vertex_isomorphic_aux(const char *x, Vertex v1, Vertex v2, int n, int i)
{
    if (i > factorial(n) - 1) {
        return 0;
    }

    if (vertex_children_equals(x, v1, v2)) {

        return vertex_isomorphic(x, v1->c, v2->c);

    } else {

        vertex_permute(v2, i);

        if (vertex_children_equals(x, v1, v2)) {

            return vertex_isomorphic(x, v1->c, v2->c);

        } else {

            vertex_permute_inverse(v2, i);

        }

    }
    return vertex_isomorphic_aux(x, v1, v2, n, ++i);
}

int vertex_isomorphic(const char *x, Vertex v1, Vertex v2)
{
    if (v1 && v2) {
        Vertex probe1, probe2;
        probe1 = v1;
        probe2 = v2;
        int n = 0;
        while (probe1 && probe2) {
            probe1 = probe1->s;
            probe2 = probe2->s;
            n++;
        }

        // Do the two root nodes have the same number of children?
        if (probe1 || probe2) {
            return 0;
        } else {
            return vertex_isomorphic_aux(x, v1, v2, n, 0);
        }
    } else {
        return !v1 && !v2;
    }
}


void vertex_print(const Vertex v)
{
    printf("<%d, %d, %d>\n", v->l->i, v->l->j, v->k);
}
