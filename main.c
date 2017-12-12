
#include "stree.h"
#include "writer.h"
#include "ukkonen.h"

int main()
{

    Stree x = stree_init("x");
    Stree u = ukkonen_naive();

    stree_extend(x, u);

    write_stree_to_file(x, "../suffix-trees-haskell/data/sample");

    return 0;
}
