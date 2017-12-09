
#include "ukkonen.h"

void sstring(char *s, int i, int n, char *buf)
{
    char subbuff[n + 1];
    memcpy(subbuff, &s[i], n);
    subbuff[n] = '\0';
    sprintf(buf, "%s", subbuff);
}

void ukkonen_naive() {
    char *t = "abc";
    Stree i1 = stree_init("hello");
    size_t len = strlen(t);
    for (unsigned long i = 1; i <= len; i++) {
        for(unsigned long j = 0; j < i; j++) {
            char buf[8];
            sstring(t, j, i - j, buf);
            printf("%s\n", buf);
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


