
#include "ukkonen.h"

Stree ukkonen_naive() {
    char *text = "abaababa";
    Stree tree = stree_init(text);
    size_t len = strlen(text);
    /* for (unsigned long i = 1; i <= len; i++) { */
        /* for(unsigned long j = 0; j < i; j++) { */
    for (unsigned long i = 3; i <= 4; i++) {
        for(unsigned long j = 0; j < i - 1; j++) {
        printf("\n-------Step: %zu, Phase %zu-----\n\n", i - 2, j);

            char t[8];
            char t_init[8];
            size_t t_len = i - j - 1;

            sstring(text, j, t_len, t);
            sstring(text, j, t_len - 1, t_init);
            char a = t[t_len - 1];

            printf("Searching for: %s\n", t_init);
            Stree end = stree_find(tree, t_init).tree;

            if (end) {

                // TODO At this point we found the end. Now we need to check if
                // we are at the last character. In that case extend.
                // Otherwise, need to insert inner node.
                //

                printf("Matched. Extending: %s with %c\n", end->lbl->mark, a);
                label_extend_letter(end->lbl, a);
                printf("Result: %s\n", end->lbl->mark);

            } else {

                printf("\nNot matched: label: %s, char: %c\n\n", tree->lbl->mark, a);
                printf("Trying right sibling...\n");

                EdgePointer probe = tree;
                int matching_branch = 0;
                while (probe) {
                    if (probe->lbl->mark[0] == a) {
                        matching_branch = 1;
                        break;
                    }
                    probe = probe->right;
                }
                if (!matching_branch) {
                    char *mark = malloc(sizeof(char) * STRING_INIT_LEN);
                    sprintf(mark, "%c", a);
                    EdgePointer right_edge = edge_from_mark(mark);
                    stree_extend_right(tree, right_edge);
                    printf("No matching sibling. Create new edge with: %s\n",
                            right_edge->lbl->mark); 
                } else {
                    printf("Doing nothing\n");
                }
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


