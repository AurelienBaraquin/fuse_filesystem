#include "tree.h"
#include "ffuse.h"
#include "compressor.h"

//* READ ___________________________________________________________________*/
int ffuse_read(const char *path, char *buf, size_t size, off_t offset, struct fuse_file_info *fi) {
    (void) fi;
    if (buf == NULL || size == (unsigned long)0) {
        return -EINVAL;
    }

    lock_tree();

    struct node *file = get_file(path);
    if (file == NULL) {
        RETURN_UNLOCK_TREE(-ENOENT);
    }

    if (!S_ISREG(file->stat.st_mode)) {
        RETURN_UNLOCK_TREE(-EISDIR);
    }

    decompress_content(file);

    if (offset >= file->stat.st_size) {
        RETURN_UNLOCK_TREE(0);
    }

    size_t bytes_to_read = size;
    if (offset + size > (unsigned long)file->stat.st_size) {
        bytes_to_read = file->stat.st_size - offset;
    }

    memcpy(buf, file->content + offset, bytes_to_read);
    file->stat.st_atime = time(NULL);

    compress_content(file);

    RETURN_UNLOCK_TREE(bytes_to_read);
}
