#include "fd.h"
#include <pthread.h>
#include <string.h>

/* File descriptor table */
fd_t fd_table[MAX_FILES];

/* Mutex for the file descriptor table */
static pthread_mutex_t fd_table_mutex = PTHREAD_MUTEX_INITIALIZER;

void init_fd_table(void) {
    pthread_mutex_lock(&fd_table_mutex);

    memset(fd_table, 0, sizeof(fd_table));

    pthread_mutex_unlock(&fd_table_mutex);
}

int allocate_fd(node_t *node) {
    pthread_mutex_lock(&fd_table_mutex);

    for (int i = 0; i < MAX_FILES; i++) {
        if (fd_table[i].attribued == 0) {
            fd_table[i].attribued = 1;
            fd_table[i].node = node;
            pthread_mutex_unlock(&fd_table_mutex);
            return i;
        }
    }

    pthread_mutex_unlock(&fd_table_mutex);
    return -1;
}

void release_fd(int fd) {
    pthread_mutex_lock(&fd_table_mutex);

    if (fd >= 0 && fd < MAX_FILES) {
        fd_table[fd].attribued = 0;
    }

    pthread_mutex_unlock(&fd_table_mutex);
}

fd_t *get_fd(int fd) {
    pthread_mutex_lock(&fd_table_mutex);

    if (fd >= 0 && fd < MAX_FILES) {
        pthread_mutex_unlock(&fd_table_mutex);
        return &fd_table[fd];
    }

    pthread_mutex_unlock(&fd_table_mutex);
    return ((void *)0);
}

fd_t *get_fd_from_node(node_t *node) {
    pthread_mutex_lock(&fd_table_mutex);

    for (int i = 0; i < MAX_FILES; i++) {
        if (fd_table[i].attribued == 1 && fd_table[i].node == node) {
            pthread_mutex_unlock(&fd_table_mutex);
            return &fd_table[i];
        }
    }

    pthread_mutex_unlock(&fd_table_mutex);
    return ((void *)0);
}
