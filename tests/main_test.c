#include <check.h>
#include <stdlib.h>
#include <stdio.h>
#include "tree.h"

Suite * tree_suite(void);
Suite * compressor_suite(void);

//* RUN TESTS ___________________________________________________________________*/
int main(void) {
    int number_failed;
    SRunner *sr;

    sr = srunner_create(NULL);

    srunner_add_suite(sr, tree_suite());
    srunner_add_suite(sr, compressor_suite());


    srunner_run_all(sr, CK_NORMAL);
    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);
    return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
