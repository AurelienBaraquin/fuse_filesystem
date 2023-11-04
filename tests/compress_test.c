#include <check.h>
#include <stdlib.h>
#include <stdio.h>
#include "compressor.h"

//* SETUP ______________________________________________________________________*/
static void setup(void) {
    init_root();
}

static void teardown(void) {
    free_tree(sys_get_root());
}

//* Compress a file ____________________________________________________________*/
START_TEST(test_compress_content) {
    node_t *file = sys_add_file("/testfile");
    ck_assert_ptr_nonnull(file);
    file->content = (unsigned char *)strdup("testfile");
    ck_assert_int_eq(compress_content(file), 0);
}

//* Compress a file, then decompress it and check if the content is the same ___*/
START_TEST(test_compress_decompress_content) {
    node_t *file = sys_add_file("/testfile");
    ck_assert_ptr_nonnull(file);
    file->content = (unsigned char *)strdup("testfile");
    file->stat.st_size = strlen((char *)file->content);
    ck_assert_int_eq(compress_content(file), 0);
    ck_assert_int_eq(decompress_content(file), 0);
    ck_assert_str_eq((char *)file->content, "testfile");
}

Suite * compressor_suite(void) {
    Suite *s;
    TCase *tc_core;

    s = suite_create("Compressor");

    tc_core = tcase_create("Core");

    tcase_add_checked_fixture(tc_core, setup, teardown);

    tcase_add_test(tc_core, test_compress_content);
    tcase_add_test(tc_core, test_compress_decompress_content);

    suite_add_tcase(s, tc_core);

    return s;
}
