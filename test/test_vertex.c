
#include "test.h"
#include "vertex.h"


static char *utest_test_vertex_branches_with()
{
    char *x = "aba";

    Vertex v = vertex(0, 1);
    Vertex v2 = vertex(1, 2);

    vertex_extend_below(v, v2);

    int b = vertex_branches_with(x, v, 'a');

    printf("%d\n", b);


    return NULL;
}

char *test_vertex()
{
    mu_run_utest(utest_test_vertex_branches_with);
    return NULL;
}
