#pragma once

#include "node.h"

void set_store_dir(char *dir);
char *get_store_dir(void);

int store_file(char *filepath, unsigned char *buffer);
int read_file(char *filepath, unsigned char *buffer);

int store_node(node_t *node, unsigned char *buffer);
unsigned char *read_node(node_t *node);
