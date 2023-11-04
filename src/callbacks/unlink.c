#include "tree.h"
#include "ffuse.h"

int ffuse_unlink(const char *path)
{
    lock_tree();

    node_t *file = get_file(path);
    if (!path)
        RETURN_UNLOCK_TREE(-ENOENT);

    if (file->stat.st_nlink > 1)
        RETURN_UNLOCK_TREE(-EEXIST);
    if (file->stat.st_mode & S_IFDIR)
        RETURN_UNLOCK_TREE(-EISDIR);

    int ret = sys_remove_file(path);

    unlock_tree();
    return ret;
}
