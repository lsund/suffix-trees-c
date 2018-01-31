#ifndef LABEL_H
#define LABEL_H

#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "config.h"
#include "util.h"

typedef struct label {
    const char *s;
    size_t len;
    int i, j;
} *Label;

typedef struct label2 {
    int i, j;
} *Label2;

Label2 label2(int i, int j);

Label label(const char *s, const int i, const int j);

Label label_full(char *mark);

void label_mark(Label l, char *mark);

// Shrink label at the left side
void label_shrink_left(Label l, const int n);

void label_set_right(Label l, const int i);

char label_char_at(Label l, int i);

void label_extend(const Label l);

void label_print(Label l);

void label_destroy(Label l);

///////////////////////////////////////////////////////////////////////////////
// new

char label_char_at_2(const char *s, const Label2 lbl, const int i);

void label_shrink_left2(const Label2 lbl, const int n);

void label_extend_right2(const Label2 lbl);

void label_set_right2(const Label2 lbl, const int i);

void label_mark2(char *t, const Label2 lbl, const char *s);
#endif
