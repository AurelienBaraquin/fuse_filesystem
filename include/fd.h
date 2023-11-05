#pragma once

#include "node.h"

typedef struct fd {
    char is_used : 1;
    node_t *node;
} fd_t;
