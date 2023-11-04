#include "tree.h"
#include "ffuse.h"

//* CHMOD ____________________________________________________________________*/
int ffuse_chmod(const char *path, mode_t mode, struct fuse_file_info *fi)
{
    lock_tree();
    (void) fi;
    struct node *file = get_file(path);
    if (file == NULL)
        RETURN_UNLOCK_TREE(-ENOENT);
    file->stat.st_mode = mode;
    file->stat.st_ctime = time(NULL);
    RETURN_UNLOCK_TREE(0);
}
