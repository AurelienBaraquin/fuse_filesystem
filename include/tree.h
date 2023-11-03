#pragma once

#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

#define MAX_CHILD 100

typedef struct node {
    char *name;
    char *content;
    size_t size;
    struct node *parent;
    struct node *childs[MAX_CHILD];
} node_t;

/*  type    |   name     |   content |   size    |   parent  |   childs
    reg     |     Y      |     Y     |     Y     |Y (no root)|      N
    dir     |     Y      |     N     |     N     |Y (no root)|      Y
    root    |   ("/")    |     N     |     N     |     N     |      Y
*/

// strrchr: find the last occurence of any char in a string

int sys_add_file(const char *path);
int sys_remove_file(const char *path);
node_t *get_node(const char *path);
void print_tree(void);
void free_tree(node_t *node);
node_t *sys_get_root(void);
