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
    const char *text;
    size_t len;
    int i, j;
} *LabelPointer;

LabelPointer label2(const char *text, int i, int n);
LabelPointer label(char *mark);

// Shrink label at the left side
void label_shrink_left(LabelPointer lbl, int k);

void label_set_right(LabelPointer lbl, int k);

char label_char_at(LabelPointer lbl, int i);

void label_extend(const LabelPointer lbl, const char c);

void label_print(LabelPointer lbl);
void label_print2(LabelPointer lbl);

void label_destroy(LabelPointer lbl);

#endif
