#include "tree.h"
#include "ffuse.h"
#include "utils.h"

//* CREATE ____________________________________________________________________*/
int ffuse_create(const char *path, mode_t mode, struct fuse_file_info *fi)
{
    lock_tree();

    create_entry(path, mode | S_IFREG);

    unlock_tree();
    return 0;
}
