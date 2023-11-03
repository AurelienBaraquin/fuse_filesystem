#include "tree.h"
#include "ffuse.h"
#include "callbacks.h"

static int ffuse_create(const char *path, mode_t mode, struct fuse_file_info *fi)
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

static struct fuse_operations ffuse_oper = {
    .getattr = ffuse_getattr,
    .readdir = ffuse_readdir,
    // .open = ffuse_open,
    // .read = ffuse_read,
    // .write = ffuse_write,
    .create = ffuse_create,
    // .unlink = ffuse_unlink,
    // .mkdir = ffuse_mkdir,
    // .rmdir = ffuse_rmdir,
    // .rename = ffuse_rename,
    // .truncate = ffuse_truncate,
    // .utimens = ffuse_utimens,
    // .chmod = ffuse_chmod,
    // .chown = ffuse_chown,
    // .link = ffuse_link,
    // .symlink = ffuse_symlink,
    // .readlink = ffuse_readlink,
    // .release = ffuse_release,
    // .destroy = ffuse_destroy,
};

int main(int argc, char *argv[])
{
    init_root();
    return fuse_main(argc, argv, &ffuse_oper, NULL);
}
