#include "tree.h"
#include "ffuse.h"
#include <stdio.h>

//* READDIR ___________________________________________________________________*/
int ffuse_readdir(const char *path, void *buf, fuse_fill_dir_t filler, off_t offset, struct fuse_file_info *fi, enum fuse_readdir_flags flags)
{
    (void)offset;
    (void)fi;
    (void)flags;

    if (!path)
        return -ENOENT;
    node_t *dir = get_file(path);
    if (!dir)
        return -ENOENT;

    lock_tree();
    for (int i = 0; i < MAX_CHILD; i++)
    {
        if (dir->childs[i]) {
            print_tree();
            filler(buf, dir->childs[i]->name, &dir->childs[i]->stat, 0, FUSE_FILL_DIR_PLUS);
        }
    }
    unlock_tree();

    return 0;
}
