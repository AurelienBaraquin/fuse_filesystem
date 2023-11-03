#include "tree.h"
#include "ffuse.h"

//* WRITE ___________________________________________________________________*/
int ffuse_write(const char *path, const char *buf, size_t size, off_t offset, struct fuse_file_info *fi)
{
    lock_tree();
    (void) fi;
    struct node *node = get_file(path);
    if (node == NULL) {
        RETURN_UNLOCK_TREE(-ENOENT);
    }
    if (offset + size > node->stat.st_size) {
        node->content = realloc(node->content, offset + size);
        if (node->content == NULL) {
            RETURN_UNLOCK_TREE(-ENOMEM);
        }
        node->stat.st_size = offset + size;
    }
    memcpy(node->content + offset, buf, size);
    RETURN_UNLOCK_TREE(size);
}
