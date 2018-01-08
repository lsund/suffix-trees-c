#ifndef UTIL_H
#define UTIL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int runtime_error(const char *msg);

void sstring(char *dst, const int i, const int n, const char *src);

void extend(char *s, char c);

int char_to_int(char c);

#endif
