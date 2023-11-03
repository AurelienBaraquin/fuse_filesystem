#include "tree.h"

// Test the tree
int main(void)
{
    sys_add_file("/home");
    sys_add_file("/home/user");
    sys_add_file("/home/user/file.txt");
    sys_add_file("/home/user/file2.txt");
    sys_add_file("/home/lala");
    sys_add_file("/home/lala/file.txt");
    print_tree();
    sys_remove_file("/home/lala");
    free_tree(sys_get_root());
}
