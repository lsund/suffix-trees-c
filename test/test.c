/*****************************************************************************

* File Name: test.c

* Author: Ludvig Sundström

* Description:

* Creation Date: 16-07-2015

*****************************************************************************/

#include "test.h"

int entry_index;
int tests_run, utests_run;

static char *test()
{
    mu_message(MODULE, "util\n");
    mu_run_test(test_util);
    mu_message(MODULE, "label\n");
    mu_run_test(test_label);
    mu_message(MODULE,"matching\n");
    mu_run_test(test_matching);
    mu_message(MODULE, "writer\n");
    mu_run_test(test_writer);
    mu_message(MODULE, "reader\n");
    mu_run_test(test_reader);
    mu_message(MODULE,"stree\n");
    mu_run_test(test_stree);
    mu_message(MODULE,"stree_compare\n");
    mu_run_test(test_stree_compare);
    mu_message(MODULE,"stree_permute\n");
    mu_run_test(test_stree_permute);
    mu_message(MODULE,"ukkonen\n");
    mu_run_test(test_ukkonen);
    mu_message(MODULE,"ukkonen\n");
    mu_run_test(test_vertex_ukkonen);
    return 0;
}



void mu_message(enum MessageOption option, const char *s)
{
    switch (option) {
        case MODULE:
            fprintf(
                stdout,
                ANSI_COLOR_YELLOW "Testing Module: %s" ANSI_COLOR_RESET,
                s
            );
            break;
        case UNIT:
            fprintf(
                stdout,
                ANSI_COLOR_CYAN "\tTesting Unit: %s" ANSI_COLOR_RESET,
                s
            );
            break;
        case DATA:
            fprintf(
                stdout,
                ANSI_COLOR_GREY "\t%s" ANSI_COLOR_RESET,
                s
            );
            break;
        case PASSING:
            fprintf(
                stdout,
                ANSI_COLOR_GREEN "\t\tPassed" ANSI_COLOR_RESET "\n"
            );
            break;
        case STATISTICS:
            fprintf(
                stdout,
                ANSI_COLOR_RESET "%s" ANSI_COLOR_RESET,
                s
            );
            break;
        case PREPEND:
            fprintf(
                stdout, ANSI_COLOR_GREY "%s" ANSI_COLOR_RESET,
                s
            );
            break;
        case ERROR:
            fprintf(
                stdout, ANSI_COLOR_RED   "Error >> %s" ANSI_COLOR_RESET "\n",
                s
            );
            break;
        case TESTSPASSED:
            fprintf(
                stdout,
                ANSI_COLOR_GREEN "ALL TESTS PASSED" ANSI_COLOR_RESET "\n"
            );
            break;
    }
}

static char *all_tests() {
    char *result;
    if ((result = test())) { return result; }

    return 0;
}

int main(int argc, char **argv) {
    char *result;
    char buf1[128], buf2[128];
    argc        = 0;
    argv        = NULL;
    entry_index = -1;
    tests_run   = 0;
    utests_run  = 0;
    result      = all_tests();
    if (result != 0) {
        mu_message(ERROR, result);
    } else {
        sprintf(buf1, "Modules tested: %d\n", tests_run);
        sprintf(buf2, "Unit tests run: %d\n", utests_run);
        mu_message(STATISTICS, buf1);
        mu_message(STATISTICS, buf2);
        mu_message(TESTSPASSED, "");
    }
    return result != 0;
}

