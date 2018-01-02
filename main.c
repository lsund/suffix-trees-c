
#include "stree.h"
#include "writer.h"
#include "ukkonen.h"

int main()
{

    char *text = "abaababa";

    STree root = edge_from_string("root");;
    STree u = ukkonen_naive(text);

    stree_extend_edge_below(root, u);

    write_stree_to_file(root, "../suffix-trees-haskell/data/sample");

    stree_destroy(root);

    return 0;
}
