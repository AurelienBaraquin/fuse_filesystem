#include "tree.h"
#include "ffuse.h"
#include "fd.h"

int apply_lock(fd_t *fd, int cmd, struct flock *lock) {

    //* SETLK _____________________________*/
    if (cmd == F_SETLK) {
        if (fd->lock.is_locked) {
            if (fd->lock.pid != lock->l_pid && fd->lock.lock_type != F_UNLCK) {
                return -EACCES;
            }
        }

        if (lock->l_type == F_UNLCK) {
            // Free lock
            fd->lock.is_locked = 0;
            fd->lock.pid = 0;
            fd->lock.lock_type = F_UNLCK;
        } else {
            // Set lock
            fd->lock.is_locked = 1;
            fd->lock.pid = lock->l_pid;
            fd->lock.lock_type = lock->l_type;
        }


    //* GETLK _____________________________*/
    } else if (cmd == F_GETLK) {
        if (fd->lock.is_locked && fd->lock.pid != lock->l_pid) {
            // Say to the caller that the file is locked
            lock->l_type = fd->lock.lock_type;
            lock->l_pid = fd->lock.pid;
        } else {
            // Say to the caller that the file is unlocked
            lock->l_type = F_UNLCK;
        }
    }

    return 0;
}

//* LOCK ______________________________________________________________________*/
int ffuse_lock(const char *path, struct fuse_file_info *fi, int cmd, struct flock *lock) {
    return apply_lock(get_fd((int)fi->fh), cmd, lock);
}
