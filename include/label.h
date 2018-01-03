#ifndef LABEL_H
#define LABEL_H

#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "config.h"

typedef struct label {
    char *mark;
    size_t len;
    int i, n;                  // offset TODO add one more
} *LabelPointer;

LabelPointer label(char *mark);

void label_extend(const LabelPointer lbl, const char c);

void label_print(LabelPointer lbl);

void label_destroy(LabelPointer lbl);

#endif
