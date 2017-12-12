
#include "ukkonen.h"

Stree ukkonen_naive() {
    char *text = "abaababa";
    Stree tree = stree_init(text);
    size_t len = strlen(text);
    /* for (unsigned long i = 1; i <= len; i++) { */
        /* for(unsigned long j = 0; j < i; j++) { */
    for (unsigned long i = 3; i <= 3; i++) {
        for(unsigned long j = 0; j < i - 1; j++) {

            char t[8];
            char t_init[8];
            size_t t_len = i - j - 1;

            sstring(text, j, t_len, t);
            sstring(text, j, t_len - 1, t_init);
            char a = t[t_len - 1];

            printf("sub: %s \n", t);
            printf("init: %s \n", t_init);
            printf("a: %c \n", a);

            EdgePointer end = stree_find(tree, t_init);
            if (end) {
                // If The end of the path was found, extend the marking
                label_extend_letter(end->lbl, a);
                printf("End: %s %p\n", end->lbl->mark, end);
            } else {
                // Otherwise, add a new edge
                char *mark = malloc(sizeof(char) * STRING_INIT_LEN);
                sprintf(mark, "%c", a);
                EdgePointer right_edge = edge_from_mark(mark);
                stree_extend_right(tree, right_edge);
            }
        }
    }
    return tree;
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


