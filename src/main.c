#include "tree.h"
#include "ffuse.h"
#include "callbacks.h"

static struct fuse_operations ffuse_oper = {
    .getattr = ffuse_getattr,
    // .setxattr = ffuse_setxattr,
    .readdir = ffuse_readdir,
    // .open = ffuse_open,
    .read = ffuse_read,
    .write = ffuse_write,
    .create = ffuse_create,
    .unlink = ffuse_unlink,
    .mkdir = ffuse_mkdir,
    .rmdir = ffuse_rmdir,
    .rename = ffuse_rename,
    .truncate = ffuse_truncate,
    // .utimens = ffuse_utimens,
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
