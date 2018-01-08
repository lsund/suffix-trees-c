#ifndef EDGE_H
#define EDGE_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#include "config.h"
#include "util.h"
#include "label.h"
#include "matching.h"


// This represents both the edge itself and a suffix tree due to its recursive
// nature.
typedef struct edge {
    LabelPointer lbl;
    struct edge *child;
    struct edge *right;
} Edge, *EdgePointer;

const char *edge_str(const EdgePointer e);

EdgePointer edge_empty();

EdgePointer edge_from_letter(const char c);

EdgePointer edge_from_substring(int i, int n, char *s);

EdgePointer edge_from_string(char *string);

EdgePointer edge_from_label(const LabelPointer lbl);

#endif
