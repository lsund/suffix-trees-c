
#include "stree_permute.h"


void stree_permute(STree st, int i)
{
    int j;
    int n = 0;
    int ord[64];
    char seq[STRING_MAX_LEN];
    char perm[STRING_MAX_LEN];
    Edge siblings[64], scan;

    scan = st->c;
    while (scan) {
        siblings[n] = scan;
        scan = scan->s;
        n++;
    }
    if (!n) {
        return;
    }
    if (i > factorial(n) - 1) {
        runtime_error("stree_permute: permutation index too damn high!");
        return;
    }

    nat_sequence(seq, n);
    nth_permutation(perm, i, seq);

    for (j = 0; j < n; j++) {
        ord[j] = char_to_int(perm[j]);
    }

    st->c = siblings[ord[0]];

    for (j = 0; j < n - 1; j++) {
        siblings[ord[j]]->s = siblings[ord[j + 1]];
    }

    siblings[ord[n - 1]]->s = NULL;

}


void stree_permute_inverse(STree t, int i)
{
    int n = edge_n_siblings(t);
    stree_permute(t, permutation_inverse_number(i, n));
}


