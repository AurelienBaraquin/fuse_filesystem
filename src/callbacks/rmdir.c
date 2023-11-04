#include "tree.h"
#include "ffuse.h"

//* RMDIR ____________________________________________________________________*/
int ffuse_rmdir(const char *path)
{
    lock_tree();

    node_t *dir = get_file(path);
    if (!dir)
        RETURN_UNLOCK_TREE(-ENOENT);

    if (dir->stat.st_nlink > 2)
        RETURN_UNLOCK_TREE(-ENOTEMPTY);
    if (!(dir->stat.st_mode & S_IFDIR))
        RETURN_UNLOCK_TREE(-ENOTDIR);

    int ret = sys_remove_file(path);

    unlock_tree();
    return ret;
}
