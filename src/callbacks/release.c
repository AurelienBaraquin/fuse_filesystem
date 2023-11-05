#include "tree.h"
#include "ffuse.h"
#include "fd.h"

//* RELEASE __________________________________________________________________*/
int ffuse_release(const char *path, struct fuse_file_info *fi) {
    int fd = (int)fi->fh;
    release_fd(fd);
    return 0;
}
