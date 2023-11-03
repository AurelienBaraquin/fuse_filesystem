#include "tree.h"
#include "ffuse.h"

//* CREATE ____________________________________________________________________*/
int ffuse_create(const char *path, mode_t mode, struct fuse_file_info *fi)
{
    lock_tree();

    // Create new file node
    node_t *file = sys_add_file(path);
    if (!file)
        RETURN_UNLOCK_TREE(-ENOENT);

    // Set file attributes
    file->stat.st_mode = S_IFREG | mode;
    file->stat.st_nlink = 1;
    file->stat.st_size = 0;
    file->stat.st_uid = getuid();
    file->stat.st_gid = getgid();
    file->stat.st_atime = time(NULL);
    file->stat.st_mtime = time(NULL);
    file->stat.st_ctime = time(NULL);

    print_tree();
    unlock_tree();
    return 0;
}