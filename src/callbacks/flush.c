#include "tree.h"
#include "ffuse.h"

//* FLUSH ___________________________________________________________________*/
int ffuse_flush(const char *path, struct fuse_file_info *fi)
{
    (void) path;
    (void) fi;
    return 0;
}
