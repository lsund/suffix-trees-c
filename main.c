
#include "stree.h"
#include "writer.h"
#include "ukkonen.h"

int main()
{

    /* char *text = "abaababa"; // adv alg */
    char *text = "acbcabcac";

    STree u = ukkonen_naive(text);

    write_file("../suffix-trees-haskell/data/sample", u);

    stree_destroy(u);

    return 0;
}
