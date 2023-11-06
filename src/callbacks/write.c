#include "tree.h"
#include "ffuse.h"
#include "compressor.h"
#include "fd.h"

//* WRITE ___________________________________________________________________*/
int ffuse_write(const char *path, const char *buf, size_t size, off_t offset, struct fuse_file_info *fi)
{
    lock_tree();
    (void) fi;
    struct node *node = get_file(path);
    if (node == NULL) {
        RETURN_UNLOCK_TREE(-ENOENT);
    }

    if (!S_ISREG(node->stat.st_mode)) {
        RETURN_UNLOCK_TREE(-EISDIR);
    }

    decompress_content(node);

    node->content = realloc(node->content, offset + size);
    if (node->content == NULL) {
        RETURN_UNLOCK_TREE(-ENOMEM);
    }

    memcpy(node->content + offset, buf, size);
    node->stat.st_size = offset + size;
    node->stat.st_mtime = time(NULL);

    compress_content(node);

    RETURN_UNLOCK_TREE(size);
}