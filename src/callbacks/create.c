#include "tree.h"
#include "ffuse.h"
#include "utils.h"

//* CREATE ____________________________________________________________________*/
int ffuse_create(const char *path, mode_t mode, struct fuse_file_info *fi)
{
    lock_tree();

    if (get_file(path) != NULL)
        RETURN_UNLOCK_TREE(-EEXIST);

    node_t *file = create_entry(path, mode | S_IFREG);
    if (file == NULL)
        RETURN_UNLOCK_TREE(-ENOMEM);

    unlock_tree();
    return 0;
}
