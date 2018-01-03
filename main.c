
#include "stree.h"
#include "writer.h"
#include "ukkonen.h"

int main()
{

    char *text = "abaababa";

    STree r = edge_from_string("root");;
    STree u = ukkonen_naive(text);

    stree_extend_edge_below(r, u);

    write_stree_to_file(r, "../suffix-trees-haskell/data/sample");

    stree_destroy(r);

    return 0;
}
