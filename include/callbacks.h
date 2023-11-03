#pragma once

#include <fuse.h>

int ffuse_getattr(const char *path, struct stat *stbuf, struct fuse_file_info *fi);
int ffuse_readdir(const char *path, void *buf, fuse_fill_dir_t filler, off_t offset, struct fuse_file_info *fi, enum fuse_readdir_flags flags);
int ffuse_create(const char *path, mode_t mode, struct fuse_file_info *fi);
int ffuse_write(const char *path, const char *buf, size_t size, off_t offset, struct fuse_file_info *fi);
int ffuse_read(const char *path, char *buf, size_t size, off_t offset, struct fuse_file_info *fi);
