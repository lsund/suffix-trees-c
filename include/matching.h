#ifndef MATCHING_H
#define MATCHING_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "vertex.h"
#include "label.h"
#include "util.h"

///////////////////////////////////////////////////////////////////////////////
// Enums


typedef enum { NONE, EXACT, PARTIAL_RIGHT, PARTIAL_LEFT } MatchType;


///////////////////////////////////////////////////////////////////////////////
// Structs


typedef struct matching {
    int n;
    int l;
    int r;
} Matching;


///////////////////////////////////////////////////////////////////////////////
// Functions

Matching matching_empty();

MatchType match_type(const Matching m);

Matching match(const Label l1, const Label l2);

///////////////////////////////////////////////////////////////////////////////
// new

Matching match2(const char *x, const Label2 l1, const Label2 l2);
#endif
