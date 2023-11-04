#include "tree.h"
#include "ffuse.h"
#include "utils.h"
#include "perm.h"

//* OPEN ______________________________________________________________________*/
/* Only check if the file can be open, we need implement neither O_CREAT nor O_TRUNC */
int ffuse_open(const char *path, struct fuse_file_info *fi) {
    lock_tree();

    if (strcmp(path, "/") == 0) {
        RETURN_UNLOCK_TREE(0);
    }

    node_t *file = get_file(path);
    if (file == NULL) {
        RETURN_UNLOCK_TREE(-ENOENT);
    }

    mode_t mode = file->stat.st_mode;
    switch (fi->flags & O_ACCMODE) {
        case O_RDONLY:
            if (!(mode & S_IRUSR)) RETURN_UNLOCK_TREE(-EACCES);
            break;
        case O_WRONLY:
            if (!(mode & S_IWUSR)) RETURN_UNLOCK_TREE(-EACCES);
            break;
        case O_RDWR:
            if (!(mode & (S_IRUSR | S_IWUSR))) RETURN_UNLOCK_TREE(-EACCES);
            break;
        default:
            RETURN_UNLOCK_TREE(-EACCES);
    }

    RETURN_UNLOCK_TREE(0);
}
