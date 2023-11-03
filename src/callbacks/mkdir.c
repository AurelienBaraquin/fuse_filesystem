#include "tree.h"
#include "ffuse.h"

//* MKDIR ___________________________________________________________________*/
int ffuse_mkdir(const char *path, mode_t mode)
{
    lock_tree();

    // Create new file node
    node_t *file = sys_add_file(path);
    if (!file)
        RETURN_UNLOCK_TREE(-ENOENT);

    // Set file attributes
    file->stat.st_mode = S_IFDIR | mode;
    file->stat.st_nlink = 1;
    file->stat.st_size = 0;
    file->stat.st_uid = getuid();
    file->stat.st_gid = getgid();
    file->stat.st_atime = time(NULL);
    file->stat.st_mtime = time(NULL);
    file->stat.st_ctime = time(NULL);

    unlock_tree();
    return 0;
}
