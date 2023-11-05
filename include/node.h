#pragma once

#include <sys/stat.h>
#include <sys/types.h>

#define MAX_CHILD 100

typedef struct node {
    char *name;
    unsigned char *content;
    size_t compressed_size;
    struct stat stat;
    struct node *parent;
    struct node *childs[MAX_CHILD];
} node_t;
