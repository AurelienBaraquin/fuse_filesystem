#include "tree.h"

// Test the tree
int main(void)
{
    add_file("/home");
    add_file("/home/user");
    add_file("/home/user/file.txt");
    add_file("/home/user/file2.txt");
    add_file("/home/lala");
    add_file("/home/lala/file.txt");
    remove_file("/home/lala");
    print_tree();
    free_tree(get_root());
}
