
#ifndef TEST_H
#define TEST_H

#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdlib.h>

#include "minunit.h"
#include "config.h"

char *test_stree();

enum MessageOption {
    MODULE,
    UNIT,
    DATA,
    STATISTICS,
    PASSING,
    PREPEND,
    ERROR,
    TESTSPASSED
};

void mu_message(enum MessageOption, const char *s);

extern int tests_run;
extern int utests_run;

// Testing works the following way: Each public function in each module is
// tested. private functions are tested indirectly, because of the testing of
// the public functions. The public functions are tested for abilities to handle
// all inputs and that the outputs make sense.

#endif