#include <zlib.h>
#include "tree.h"

int decompress_content(node_t *file) {
    if (!file || !file->content)
        return -1;

    unsigned char *decompressed_data = malloc(file->stat.st_size);
    if (!decompressed_data)
        return -1;

    uLongf decompressed_size = file->stat.st_size;

    int ret = uncompress(decompressed_data, &decompressed_size, (const Bytef *)file->content, file->compressed_size);
    if (ret != Z_OK) {
        free(decompressed_data);
        return -1;
    }

    free(file->content);
    file->content = decompressed_data;
    file->stat.st_size = decompressed_size;

    return 0; // Succès
}
