#include "storage.h"
#include <stdio.h>
#include <stdlib.h>
#include "compressor.h"
#include "node.h"

//* STORE BUFFER INTO FILEPATH FROM STORE DIR ___________________________________*/
int store_file(char *filepath, unsigned char *buffer)
{
    char *fullpath = calloc(1, strlen(get_store_dir()) + strlen(filepath) + 1);
    strcat(fullpath, get_store_dir());
    strcat(fullpath, filepath);

    FILE *file = fopen(fullpath, "w");
    if (!file)
        return -1;
    fprintf(file, "%s", buffer);
    fclose(file);
    return 0;
}

//* READ FILEPATH FROM STORE DIR INTO BUFFER ____________________________________*/
int read_file(char *filepath, unsigned char *buffer)
{
    char *fullpath = calloc(1, strlen(get_store_dir()) + strlen(filepath) + 1);
    strcat(fullpath, get_store_dir());
    strcat(fullpath, filepath);

    FILE *file = fopen(fullpath, "r");
    if (!file)
        return -1;
    fscanf(file, "%s", buffer);
    fclose(file);
    return 0;
}

//* STORE COMPRESSED NODE INTO FILEPATH FROM STORE DIR __________________________*/
int store_node(node_t *node, unsigned char *buffer)
{
    if (compressBuffer(buffer, node->stat.st_size, &node->compressed_size) != 0)
        return -1;
    return store_file(node->name, buffer);
}

//* READ FILEPATH FROM STORE DIR INTO NODE ______________________________________*/
unsigned char *read_node(node_t *node)
{
    unsigned char *buffer = calloc(1, node->compressed_size);
    if (read_file(node->name, buffer) != 0)
        return NULL;
    if (decompressBuffer(buffer, node->compressed_size, (size_t *)&node->stat.st_size) != 0)
        return NULL;
    return buffer;
}
