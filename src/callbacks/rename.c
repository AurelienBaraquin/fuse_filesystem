#include "tree.h"
#include "ffuse.h"

#include <fcntl.h>
#define RENAME_EXCHANGE (1 << 1)
#define RENAME_NOREPLACE (1 << 2)


//* RENAME ___________________________________________________________________*/
int ffuse_rename(const char *oldpath, const char *newpath, unsigned int flags)
{
    (void) flags;
    int ret = -1;
    lock_tree();

    if (flags & RENAME_EXCHANGE) {
        ret = sys_rename_file(oldpath, newpath);
    } else if (flags & RENAME_NOREPLACE) {
        if (get_file(newpath))
            ret = sys_rename_file(oldpath, newpath);
        else
            ret = -1;
    } else {
        ret = sys_rename_file(oldpath, newpath);
    }

    unlock_tree();
    return ret;
}
