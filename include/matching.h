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
    const char *match;
    const char *rest_left;
    const char *rest_right;
} Matching;


///////////////////////////////////////////////////////////////////////////////
// Functions

Matching matching_empty();

MatchType match_type(const Matching match);

Matching match(const char *a, const char *b);

#endif
