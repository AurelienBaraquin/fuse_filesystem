#include "tree.h"
#include "ffuse.h"

//* READ ___________________________________________________________________*/
int ffuse_read(const char *path, char *buf, size_t size, off_t offset, struct fuse_file_info *fi)
{
    lock_tree();
    (void) fi;
    struct node *node = get_file(path);
    if (node == NULL) {
        RETURN_UNLOCK_TREE(-ENOENT);
    }
    if (offset >= node->stat.st_size) {
        RETURN_UNLOCK_TREE(0);
    }
    size_t bytes_to_read = size;
    if (offset + size > node->stat.st_size) {
        bytes_to_read = node->stat.st_size - offset;
    }
    memcpy(buf, node->content + offset, bytes_to_read);
    RETURN_UNLOCK_TREE(bytes_to_read);
}
