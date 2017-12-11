
#include "ukkonen.h"

void ukkonen_naive() {
    char *t = "abaababa";
    Stree i1 = stree_init(t);
    size_t len = strlen(t);
    /* for (unsigned long i = 1; i <= len; i++) { */
        /* for(unsigned long j = 0; j < i; j++) { */
    for (unsigned long i = 1; i <= 2; i++) {
        for(unsigned long j = 0; j < i - 1; j++) {
            char buf[8];
            sstring(t, j, i - j - 1, buf);
            printf("%s\n", buf);
            EdgePointer end = stree_find(i1, buf);
            // TODO extend marking
            printf("End: %s %p\n", end->lbl.mark, end);
        }
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


