#include "tree.h"
#include "ffuse.h"

//* TRUNCATE ___________________________________________________________________*/
int ffuse_truncate(const char *path, off_t size, struct fuse_file_info *fi)
{
    lock_tree();
    struct node *node = get_file(path);
    if (node == NULL)
        RETURN_UNLOCK_TREE(-ENOENT);

    if (size == 0) {
        free(node->content);
        node->content = NULL;
        node->stat.st_size = 0;
        RETURN_UNLOCK_TREE(0);
    }

    node->content = realloc(node->content, size);
    if (node->content == NULL)
        RETURN_UNLOCK_TREE(-ENOMEM);

    node->stat.st_size = size;
    RETURN_UNLOCK_TREE(0);
}
