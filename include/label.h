#ifndef LABEL_H
#define LABEL_H

#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "config.h"
#include "matching.h"

typedef struct label {
    char *mark;
    size_t len, max_len;
} *Label;

Label label_maxlen(const char *mark, size_t maxlen);

Label label(const char *mark);

void label_extend(const Label lbl, const char *mark);

void label_extend_letter(Label lbl, const char mark);
#endif
