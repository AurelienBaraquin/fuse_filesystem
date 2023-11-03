#include "tree.h"
#include "ffuse.h"

//* GETATTR ___________________________________________________________________*/
int ffuse_getattr(const char *path, struct stat *stbuf, struct fuse_file_info *fi)
{
    if (!path)
        return -ENOENT;

    node_t *file = get_node(path);
    if (!file)
        return -ENOENT;
    memset(stbuf, 0, sizeof(struct stat));

    stbuf->st_mode = file->stat.st_mode;
    stbuf->st_size = file->stat.st_size;
    stbuf->st_nlink = file->stat.st_nlink;
    stbuf->st_uid = file->stat.st_uid;
    stbuf->st_gid = file->stat.st_gid;
    stbuf->st_atime = file->stat.st_atime;
    stbuf->st_mtime = file->stat.st_mtime;
    stbuf->st_ctime = file->stat.st_ctime;

    return 0;
}
