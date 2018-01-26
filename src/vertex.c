
#include "vertex.h"

Vertex vertex(const int i)
{
    return vertex_leaf(i, -1);
}

Vertex vertex_leaf(const int i, const int k)
{
    Vertex v;
    v = malloc(sizeof(struct vertex));
    v->i = i;
    v->k = k;
    v->c = NULL;
    v->s = NULL;
    v->p = NULL;

    return v;
}


void label_shrink_left2(const Vertex v, const int n)
{
    v->i += n;
}


void label_extend_right2(const Vertex v)
{
    v->i++;
}


void label_set_right2(const Vertex v, const int i)
{
    v->i = i;
}


void label_mark2(const char *s, const Vertex v1, const Vertex v2, char *mark)
{
    sstring(mark, v1->i, v2->i - v1->i, s);
}


char label_char_at_2(const char *s, const Vertex v1, const Vertex v2, const int i)
{
    if (i > v2->i) {
        return '\0';
    } else {
        char tmp[64];
        tmp[0] = '\0';
        label_mark2(s, v1, v2, tmp);
        return *(tmp + v1->i + i);
    }
}


void label_print2(const char *s, const Vertex v1, const Vertex v2)
{
    char tmp[STRING_MAX_LEN];
    label_mark2(s, v1, v2, tmp);
    printf("%s\n", tmp);
}


int vertex_n_siblings(const Vertex e)
{
    int n = 0;
    Vertex scan = e->c;
    while (scan) {
        scan = scan->s;
        n++;
    }
    return n;
}


void vertex_destroy(Vertex v)
{
    free(v);
}
