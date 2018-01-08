
#include "stree.h"
#include "writer.h"
#include "ukkonen.h"

int main()
{

    char *text = "abaababa";

    STree u = ukkonen_naive(text);

    write_file(u, "../suffix-trees-haskell/data/sample");

    stree_destroy(u);

    return 0;
}
