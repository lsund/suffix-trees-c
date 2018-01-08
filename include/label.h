#ifndef LABEL_H
#define LABEL_H

#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "config.h"
#include "util.h"

typedef struct label {
    char *mark;
    size_t len;
    int i, n;
} *LabelPointer;

LabelPointer label(char *mark);

char label_char_at(LabelPointer lbl, int i);

void label_extend(const LabelPointer lbl, const char c);

void label_print(LabelPointer lbl);

void label_destroy(LabelPointer lbl);

#endif
