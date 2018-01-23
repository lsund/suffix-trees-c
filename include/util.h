#ifndef UTIL_H
#define UTIL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "config.h"

int runtime_error(const char *msg);

void sstring(char *dst, const int i, const int n, const char *src);

int char_to_int(char c);

void all_permutations(char *t, char *s);

void nth_permutation(char *t, int i, char *s);

int permutation_inverse_number(int i, int n);

void nat_sequence(char *t, int i);

int factorial(const int i);

#endif
