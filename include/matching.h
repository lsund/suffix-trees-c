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
    int success, unmatched_left, unmatched_right;
    int match_both;
} Matching;


///////////////////////////////////////////////////////////////////////////////
// Functions

Matching matching_empty();

MatchType match_type(const Matching match);

Matching match(char *a, char *b);

int matched_fully_left(Matching m);

int matched_fully_right(Matching m);

void matching_destroy(Matching m);
#endif
