#include <zlib.h>
#include "tree.h"

/* Compresses the content of a file using zlib
    * Returns 0 on success, -1 on error */
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

    return 0;
}

/* Decompresses the content of a file using zlib
    * Returns 0 on success, -1 on error */
int compress_content(node_t *file) {
    if (!file || !file->content)
        return -1;

    uLongf compressed_size = compressBound(file->stat.st_size);

    unsigned char *compressed_data = malloc(compressed_size);
    if (!compressed_data)
        return -1;

    int ret = compress(compressed_data, &compressed_size, (const Bytef *)file->content, file->stat.st_size);
    if (ret != Z_OK) {
        free(compressed_data);
        return -1;
    }

    free(file->content);
    file->content = compressed_data;
    file->compressed_size = compressed_size;

    return 0;
}

//* COMPRESS AND DECOMPRESS BUFFER ______________________________________________*/
unsigned char* compressBuffer(unsigned char* inBuffer, size_t inLength, size_t* outLength) {
    unsigned long estCompressedSize = compressBound(inLength);
    unsigned char* outBuffer = (unsigned char*)malloc(estCompressedSize);

    if (compress(outBuffer, &estCompressedSize, inBuffer, inLength) != Z_OK) {
        free(outBuffer);
        return NULL;
    }

    *outLength = estCompressedSize;
    return outBuffer;
}

unsigned char* decompressBuffer(unsigned char* inBuffer, size_t inLength, size_t* outLength) {
    unsigned long estDecompressedSize = *outLength;
    unsigned char* outBuffer = (unsigned char*)malloc(estDecompressedSize);

    if (uncompress(outBuffer, &estDecompressedSize, inBuffer, inLength) != Z_OK) {
        free(outBuffer);
        return NULL;
    }

    *outLength = estDecompressedSize;
    return outBuffer;
}
