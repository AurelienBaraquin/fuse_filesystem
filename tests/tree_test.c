#include <check.h>
#include <stdlib.h>
#include <stdio.h>
#include "tree.h"

//* SETUP ______________________________________________________________________*/
void setup(void) {
    init_root();
}

void teardown(void) {
    free_tree(sys_get_root());
}



//* ADD FILE FROM ROOT _________________________________________________________*/
START_TEST(test_sys_add_file) {
    node_t *root = sys_get_root();
    node_t *file = sys_add_file("/testfile");

    ck_assert_ptr_nonnull(file);
    ck_assert_ptr_eq(root->childs[0], file);
}

//* ADD DIR FROM ROOT __________________________________________________________*/
START_TEST(test_sys_add_dir) {
    node_t *root = sys_get_root();
    node_t *dir = sys_add_file("/testdir");

    ck_assert_ptr_nonnull(dir);
    ck_assert_ptr_eq(root->childs[0], dir);
}

//* ADD FILE FROM DIR __________________________________________________________*/
START_TEST(test_sys_add_file_from_dir) {
    node_t *dir = sys_add_file("/testdir");
    node_t *file = sys_add_file("/testdir/testfile");

    ck_assert_ptr_nonnull(file);
    ck_assert_ptr_eq(dir->childs[0], file);
}

//* ADD DIR FROM DIR ___________________________________________________________*/
START_TEST(test_sys_add_dir_from_dir) {
    node_t *dir = sys_add_file("/testdir");
    node_t *subdir = sys_add_file("/testdir/testsubdir");

    ck_assert_ptr_nonnull(subdir);
    ck_assert_ptr_eq(dir->childs[0], subdir);
}

//* LOTS OF FILES ______________________________________________________________*/
START_TEST(test_sys_add_lots_of_files) {
    node_t *dir = sys_add_file("/testdir");
    node_t *file;
    char path[100];

    for (int i = 0; i < MAX_CHILD; i++) {
        sprintf(path, "/testdir/testfile%d", i);
        file = sys_add_file(path);
        ck_assert_ptr_nonnull(file);
        ck_assert_ptr_eq(dir->childs[i], file);
    }
}

//* LOTS OF DIRS _______________________________________________________________*/
START_TEST(test_sys_add_lots_of_dirs) {
    node_t *dir = sys_add_file("/testdir");
    node_t *subdir;
    char path[100];

    for (int i = 0; i < MAX_CHILD; i++) {
        sprintf(path, "/testdir/testsubdir%d", i);
        subdir = sys_add_file(path);
        ck_assert_ptr_nonnull(subdir);
        ck_assert_ptr_eq(dir->childs[i], subdir);
    }
}

//* 5 LAYERS OF DIRS + 1 FILE IN EACH __________________________________________*/
START_TEST(five_layers_of_dirs) {
    node_t *dir = sys_add_file("/testdir");
    node_t *subdir;
    char path[100];

    for (int i = 0; i < MAX_CHILD; i++) {
        sprintf(path, "/testdir/testsubdir%d", i);
        subdir = sys_add_file(path);
        ck_assert_ptr_nonnull(subdir);
        ck_assert_ptr_eq(dir->childs[i], subdir);
    }
}

//* RENAME FILE ________________________________________________________________*/
START_TEST(test_sys_rename_file) {
    node_t *file = sys_add_file("/testfile");
    sys_rename_file("/testfile", "/testfile2");

    ck_assert_str_eq(file->name, "/testfile2");
}

//* RENAME DIR _________________________________________________________________*/
START_TEST(test_sys_rename_dir) {
    node_t *dir = sys_add_file("/testdir");
    sys_rename_file("/testdir", "/testdir2");

    ck_assert_str_eq(dir->name, "/testdir2");
}

//* RENAME FILE IN DIR __________________________________________________________*/
START_TEST(test_sys_rename_file_in_dir) {
    sys_add_file("/testdir");
    node_t *file = sys_add_file("/testdir/testfile");
    sys_rename_file("/testdir/testfile", "/testdir/testfile2");

    ck_assert_str_eq(file->name, "/testfile2");
}

//* TREE SUITE __________________________________________________________________*/
Suite * tree_suite(void) {
    Suite *s;
    TCase *tc_core;

    s = suite_create("Tree");

    /* Core test case */
    tc_core = tcase_create("Core");

    tcase_add_checked_fixture(tc_core, setup, teardown);
    tcase_add_test(tc_core, test_sys_add_file);
    tcase_add_test(tc_core, test_sys_add_dir);
    tcase_add_test(tc_core, test_sys_add_file_from_dir);
    tcase_add_test(tc_core, test_sys_add_dir_from_dir);
    tcase_add_test(tc_core, test_sys_add_lots_of_files);
    tcase_add_test(tc_core, test_sys_add_lots_of_dirs);
    tcase_add_test(tc_core, five_layers_of_dirs);
    tcase_add_test(tc_core, test_sys_rename_file);
    tcase_add_test(tc_core, test_sys_rename_dir);
    tcase_add_test(tc_core, test_sys_rename_file_in_dir);
    suite_add_tcase(s, tc_core);

    return s;
}
