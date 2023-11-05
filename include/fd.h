#pragma once

#include "node.h"

/* File lock types */
typedef struct {
    unsigned char is_locked : 1;
    int lock_type;
    pid_t pid;  // pid of the process that locked the file
} file_lock_t;

/* File descriptor */
typedef struct fd {
    unsigned char attribued : 1;
    node_t *node;
    file_lock_t lock;
} fd_t;
