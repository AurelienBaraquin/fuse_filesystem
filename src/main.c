#include "tree.h"
#include "ffuse.h"
#include "callbacks.h"

//* UTIMENS __________________________________________________________________*/
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

static struct fuse_operations ffuse_oper = {
    .getattr = ffuse_getattr,
    // .setxattr = ffuse_setxattr,
    .readdir = ffuse_readdir,
    .open = ffuse_open,
    .read = ffuse_read,
    .write = ffuse_write,
    .create = ffuse_create,
    .unlink = ffuse_unlink,
    .mkdir = ffuse_mkdir,
    .rmdir = ffuse_rmdir,
    .rename = ffuse_rename,
    .truncate = ffuse_truncate,
    .utimens = ffuse_utimens,
    .chmod = ffuse_chmod,
    // .chown = ffuse_chown,
    // .link = ffuse_link,
    // .symlink = ffuse_symlink,
    // .readlink = ffuse_readlink,
    // .release = ffuse_release,
    .destroy = ffuse_destroy,
    .init = ffuse_init,
    .flush = ffuse_flush,
};

int main(int argc, char *argv[])
{
    return fuse_main(argc, argv, &ffuse_oper, NULL);
}
