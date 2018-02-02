#ifndef WRITER_H
#define WRITER_H

#include "stree.h"

void write(char *s, const STree tree);

void write_file(const char *path, const STree tree);

///////////////////////////////////////////////////////////////////////////////
// New
void write2(char *acc, const STree2 tree);

#endif
