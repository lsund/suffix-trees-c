#ifndef LABEL_H
#define LABEL_H

#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "config.h"
#include "util.h"

typedef struct label {
    const char *text;
    size_t len;
    int i, j;
} *Label;

Label label(const char *text, int i, int n);

Label label_full(char *mark);

void label_mark(Label lbl, char *mark);

// Shrink label at the left side
void label_shrink_left(Label lbl, int k);

void label_set_right(Label lbl, int k);

char label_char_at(Label lbl, int i);

void label_extend(const Label lbl);

void label_print(Label lbl);
void label_print2(Label lbl);

void label_destroy(Label lbl);

#endif
