#pragma once

#include <fuse.h>

int ffuse_getattr(const char *path, struct stat *stbuf, struct fuse_file_info *fi);
int ffuse_readdir(const char *path, void *buf, fuse_fill_dir_t filler, off_t offset, struct fuse_file_info *fi, enum fuse_readdir_flags flags);
int ffuse_create(const char *path, mode_t mode, struct fuse_file_info *fi);
int ffuse_write(const char *path, const char *buf, size_t size, off_t offset, struct fuse_file_info *fi);
int ffuse_read(const char *path, char *buf, size_t size, off_t offset, struct fuse_file_info *fi);
int ffuse_mkdir(const char *path, mode_t mode);
void *ffuse_init(struct fuse_conn_info *conn, struct fuse_config *cfg);
void ffuse_destroy(void *private_data);
int ffuse_unlink(const char *path);
int ffuse_rename(const char *oldpath, const char *newpath, unsigned int flags);
int ffuse_rmdir(const char *path);
int ffuse_flush(const char *path, struct fuse_file_info *fi);
int ffuse_truncate(const char *path, off_t size, struct fuse_file_info *fi);
