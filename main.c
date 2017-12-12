
#include "stree.h"
#include "writer.h"
#include "ukkonen.h"

int main()
{

    Stree root = edge_from_mark("root");;
    Stree u = ukkonen_naive();

    stree_extend(root, u);

    write_stree_to_file(root, "../suffix-trees-haskell/data/sample");

    return 0;
}
