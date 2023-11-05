#include "tree.h"
#include "ffuse.h"

//* ACCESS ___________________________________________________________________*/
int ffuse_access(const char *path, int mask) {
    node_t *node = get_file(path);
    if (!node) {
        return -ENOENT;
    }

    // Get user and group id from the current process
    uid_t uid = fuse_get_context()->uid;
    gid_t gid = fuse_get_context()->gid;

    // If user is the owner of the file
    if (uid == node->stat.st_uid) {
        if ((mask & R_OK && !(node->stat.st_mode & S_IRUSR)) ||
            (mask & W_OK && !(node->stat.st_mode & S_IWUSR)) ||
            (mask & X_OK && !(node->stat.st_mode & S_IXUSR))) {
            return -EACCES;
        }
    } else if (gid == node->stat.st_gid) {
        // Right for group
        if ((mask & R_OK && !(node->stat.st_mode & S_IRGRP)) ||
            (mask & W_OK && !(node->stat.st_mode & S_IWGRP)) ||
            (mask & X_OK && !(node->stat.st_mode & S_IXGRP))) {
            return -EACCES;
        }
    } else {
        // Right for others
        if ((mask & R_OK && !(node->stat.st_mode & S_IROTH)) ||
            (mask & W_OK && !(node->stat.st_mode & S_IWOTH)) ||
            (mask & X_OK && !(node->stat.st_mode & S_IXOTH))) {
            return -EACCES;
        }
    }

    return 0;
}
