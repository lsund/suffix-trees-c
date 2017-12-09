
#include "ukkonen.h"

void ukkonen_naive() {
    char *t = "xaxa";
    Stree i1 = stree_init("hello");
    size_t len = strlen(t);
    for (unsigned long i = 0; i < len - 1; i++) {
        printf("hello\n");
    }

}


// Construct tree I1
// for i from 1 to m - 1 do
//      begin phase i + 1
//      for j from 1 to i + 1
//          begin extension j
//          find the end of the path from the root labaled S[j..i] in the
//          current tree. If needed, extend that path by adding acharacter
//          S(i+1)
//      end
// end


