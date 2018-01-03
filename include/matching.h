#ifndef MATCHING_H
#define MATCHING_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "util.h"

///////////////////////////////////////////////////////////////////////////////
// Enums


typedef enum { NONE, EXACT, PARTIAL_RIGHT, PARTIAL_LEFT } MatchType;


///////////////////////////////////////////////////////////////////////////////
// Structs


typedef struct matching {
    int size, left, right;
} Matching;


///////////////////////////////////////////////////////////////////////////////
// Functions

Matching matching_empty();

MatchType match_type(const Matching match);

Matching match(char *a, char *b);

#endif
