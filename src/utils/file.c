#include "utils.h"

/* create a new file with the given path, make sure to set reg or dir in mode */
int create_entry(const char *path, mode_t mode)
{
    node_t *file = sys_add_file(path);
    if (!file)
        return -1;
    
    file->stat.st_mode = mode;
    file->stat.st_nlink = mode & S_IFDIR ? 2 : 1;
    file->stat.st_size = 0;
    file->stat.st_uid = getuid();
    file->stat.st_gid = getgid();
    file->stat.st_atime = time(NULL);
    file->stat.st_mtime = time(NULL);
    file->stat.st_ctime = time(NULL);

    return 0;
}
