#include "tree.h"
#include "ffuse.h"
#include "compressor.h"

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
        unsigned char *new_content = realloc(node->content, offset + size);
        if (new_content == NULL) {
            RETURN_UNLOCK_TREE(-ENOMEM);
        }
        // Initialize new memory to zero if the file is extended.
        if (offset > node->stat.st_size) {
            memset(new_content + node->stat.st_size, 0, offset - node->stat.st_size);
        }
        memset(new_content + offset, 0, size);
        node->content = new_content;
        node->stat.st_size = offset + size;
    }
    memcpy(node->content + offset, buf, size);
    node->stat.st_mtime = time(NULL);

    compress_content(node);

    RETURN_UNLOCK_TREE(size);
}