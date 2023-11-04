#include "tree.h"
#include "ffuse.h"

//* CHMOD ____________________________________________________________________*/
int ffuse_chmod(const char *path, mode_t mode, struct fuse_file_info *fi)
{
    lock_tree();
    (void) fi;
    struct node *node = get_file(path);
    if (node == NULL)
        RETURN_UNLOCK_TREE(-ENOENT);
    node->stat.st_mode = mode;
    RETURN_UNLOCK_TREE(0);
}
