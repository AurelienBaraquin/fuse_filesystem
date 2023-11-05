#pragma once

#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <pthread.h>
#include "node.h"

/*  type    |   name     |   content |   size    |   parent  |   childs
    reg     |     Y      |     Y     |     Y     |     Y     |      N
    dir     |     Y      |     N     |     N     |     Y     |      Y
    root    |   ("/")    |     N     |     N     |     N     |      Y
*/

// strrchr: find the last occurence of any char in a string

/* Don't forget to fill stat struct after creating a node */
node_t *sys_add_file(const char *path);
int sys_remove_file(const char *path);
int sys_rename_file(const char *old_path, const char *new_path);
node_t *get_file(const char *path);
void print_tree(void);
void free_tree(node_t *node);

/* Not thread friendly use only in uni-threaded process */
node_t *sys_get_root(void);

void init_root(void);

void lock_tree(void);
void unlock_tree(void);

#define RETURN_UNLOCK_TREE(x) do { unlock_tree(); return x; } while(0)
