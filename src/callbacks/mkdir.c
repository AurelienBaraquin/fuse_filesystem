#include "tree.h"
#include "ffuse.h"
#include "utils.h"

//* MKDIR ___________________________________________________________________*/
int ffuse_mkdir(const char *path, mode_t mode)
{
    lock_tree();

    if (get_file(path) != NULL)
        RETURN_UNLOCK_TREE(-EEXIST);

    node_t *file = create_entry(path, mode | S_IFDIR);
    if (file == NULL)
        RETURN_UNLOCK_TREE(-ENOMEM);

    unlock_tree();
    return 0;
}
