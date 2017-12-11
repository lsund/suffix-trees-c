
#include "stree.h"
#include "writer.h"
#include "ukkonen.h"

int main()
{
    // Test
    char *text = "xaxa";
    EdgePointer i1 = stree_init(text);
    EdgePointer a1 = edge_from_mark("a");
    EdgePointer b1 = edge_from_mark("b");
    EdgePointer c1 = edge_from_mark("c");
    EdgePointer b2 = edge_from_mark("b");
    EdgePointer c2 = edge_from_mark("c");
    EdgePointer c3 = edge_from_mark("c");
    EdgePointer o1 = edge_from_mark("o");

    stree_extend(i1, a1);
    stree_extend(i1, b1);
    stree_extend(i1, c1);
    stree_extend(a1, b2);
    stree_extend(b2, c3);
    stree_extend(b1, c2);
    stree_extend(c1, o1);
    // Test
    /* write_stree_to_file(i1, "../suffix-trees/data/sample"); */

    ukkonen_naive();
    return 0;
}
