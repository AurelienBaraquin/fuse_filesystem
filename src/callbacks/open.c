#include "tree.h"
#include "ffuse.h"
#include "utils.h"
#include "perm.h"

//* OPEN ______________________________________________________________________*/
/* Only check if the file can be open, we need implement neither O_CREAT nor O_TRUNC */
int ffuse_open(const char *path, struct fuse_file_info *fi) {
    lock_tree();

    if (strcmp(path, "/") == 0)
        RETURN_UNLOCK_TREE(-ENOENT);

    if (get_file(path) == NULL) {
        RETURN_UNLOCK_TREE(-ENOENT);
    }

    if ((fi->flags & O_ACCMODE) == O_RDONLY || (fi->flags & O_ACCMODE) == O_RDWR || (fi->flags & O_ACCMODE) == O_WRONLY) {
        if (get_file(path)->stat.st_mode & S_IRUSR)
            RETURN_UNLOCK_TREE(0);
        else
            RETURN_UNLOCK_TREE(-EACCES);
    }

    RETURN_UNLOCK_TREE(0);
}
