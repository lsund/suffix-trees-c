
#include "stree.h"
#include "writer.h"
#include "ukkonen.h"

int main()
{

    char *root = malloc(sizeof(char) * 16);

    char *text = "abaababa";

    sprintf(root, "%s", "root");

    STree r = edge_from_string(root);;
    STree u = ukkonen_naive(text);

    stree_extend_edge_below(r, u);

    write_stree_to_file(r, "../suffix-trees-haskell/data/sample");

    stree_destroy(r);

    return 0;
}
