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

void label_mark(Label l, char *mark);

// Shrink label at the left side
void label_shrink_left(Label l, int k);

void label_set_right(Label l, int k);

char label_char_at(Label l, int i);

void label_extend(const Label l);

void label_print(Label l);
void label_print2(Label l);

void label_destroy(Label l);

#endif
