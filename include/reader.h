#ifndef READER_H
#define READER_H

#include <ctype.h>

#include "stree.h"

void read(const char *s, STree *tree);

void read2(const char *rep, STree2 tree);

void rep_to_string(char *x, const char *rep);

#endif
