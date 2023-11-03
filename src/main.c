#include "tree.h"
#include "ffuse.h"

//* GETATTR ___________________________________________________________________*/
static int ffuse_getattr(const char *path, struct stat *stbuf, struct fuse_file_info *fi)
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

    return 0;
}

//* READDIR ___________________________________________________________________*/
static int ffuse_readdir(const char *path, void *buf, fuse_fill_dir_t filler, off_t offset, struct fuse_file_info *fi, enum fuse_readdir_flags flags)
{
    (void)offset;
    (void)fi;
    (void)flags;

    if (!path)
        return -ENOENT;
    node_t *dir = get_node(path);
    if (!dir)
        return -ENOENT;

    filler(buf, ".", NULL, 0, FUSE_FILL_DIR_PLUS);
    filler(buf, "..", NULL, 0, FUSE_FILL_DIR_PLUS);

    for (int i = 0; i < MAX_CHILD; i++)
    {
        if (dir->childs[i])
            filler(buf, dir->childs[i]->name, NULL, 0, FUSE_FILL_DIR_PLUS);
    }

    return 0;
}

static struct fuse_operations ffuse_oper = {
    .getattr = ffuse_getattr,
    .readdir = ffuse_readdir,
    // .open = ffuse_open,
    // .read = ffuse_read,
    // .write = ffuse_write,
    // .create = ffuse_create,
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
