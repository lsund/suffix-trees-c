
#include "stree.h"
#include "writer.h"
#include "ukkonen.h"

int main()
{

    STree root = edge_from_mark("root");;
    STree u = ukkonen_naive();

    stree_extend_edge_below(root, u);

    write_stree_to_file(root, "../suffix-trees-haskell/data/sample");

    return 0;
}
