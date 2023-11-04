#include "tree.h"
#include "ffuse.h"

//* UTIMENS __________________________________________________________________*/
/* Set file access and modification times */
int ffuse_utimens(const char *path, const struct timespec *tv, struct fuse_file_info *fi)
{
    if (tv == NULL)
        return 0;

    lock_tree();

    struct node *file = get_file(path);
    if (file == NULL)
        RETURN_UNLOCK_TREE(-ENOENT);

    file->stat.st_atime = tv[0].tv_sec;
    file->stat.st_mtime = tv[1].tv_sec;

    RETURN_UNLOCK_TREE(0);
}
