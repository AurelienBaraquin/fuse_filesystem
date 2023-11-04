#include "tree.h"
#include "ffuse.h"
#include "utils.h"

//* MKDIR ___________________________________________________________________*/
int ffuse_mkdir(const char *path, mode_t mode)
{
    lock_tree();

    if (get_file(path) != NULL)
        RETURN_UNLOCK_TREE(-EEXIST);

    create_entry(path, mode | S_IFDIR);

    unlock_tree();
    return 0;
}
