#pragma once

#include "tree.h"

int compress_content(node_t *file);
int decompress_content(node_t *file);

unsigned char* compressBuffer(unsigned char* inBuffer, size_t inLength, size_t* outLength);
unsigned char* decompressBuffer(unsigned char* inBuffer, size_t inLength, size_t* outLength);
