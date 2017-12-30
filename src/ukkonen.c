
#include "ukkonen.h"

STree ukkonen_naive() {
    char *text = "abaababa";
    STree tree = stree_init(text);
    /* size_t len = strlen(text); */
    /* for (unsigned long i = 1; i <= len; i++) { */
        /* for(unsigned long j = 0; j < i; j++) { */
    for (unsigned long i = 3; i <= 5; i++) {
        for(unsigned long j = 0; j < i - 1; j++) {
        printf("\n-------Step: %zu, Phase %zu-----\n\n", i - 2, j);

            char t[8];
            char t_init[8];
            size_t t_len = i - j - 1;

            sstring(t, j, t_len, text);
            sstring(t_init, j, t_len - 1, text);
            char a = t[t_len - 1];

            printf("Finding %s in %s\n", t_init, tree->lbl->mark);
            TreeMatching tm = stree_find(tree, t_init);
            STree end = tm.tree;

            if (tm.m.success) {

                // TODO have to extend where the matching stopped.
                printf("Matched %s of the label\n", tm.m.match);

                if (match_type(tm.m) == EXACT) {
                    label_extend_letter(end->lbl, a);
                    printf("Extended edge with %c. Result: %s\n", a, end->lbl->mark);
                } else {
                    if (!tm.m.match) {
                        if (!stree_branch_with(tree, a)) {
                            printf("No matching\n");
                            EdgePointer new = edge_from_letter(a);
                            // TODO Might not add at root
                            stree_extend_edge_right(tree, new);
                            printf("Extended tree with new edge: %c\n", a);
                            // TODO Continue here
                            // If no matching is found, need to create a new right
                            // edge
                        } else {
                            printf("Doing nothing..\n");
                        }
                    } else {
                        printf("Matching found but not exact\n");
                        // TODO If a matching is found, need to insert a new leaf
                        // node.
                    }
                }

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


