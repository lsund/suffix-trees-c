#ifndef UTIL_H
#define UTIL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "config.h"

int runtime_error(const char *msg);

void sstring(char *dst, const int i, const int n, const char *src);

int char_to_int(char c);

void all_permutations(char *s, char *t);

void nth_permutation(int i, char *s, char *t);

void nat_sequence(int i, char *t);

int factorial(const int i);

#endif
