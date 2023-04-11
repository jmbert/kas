#pragma once

#include "tokens.h"

typedef struct _Node {
    struct _Node **children;
    int child_count;
    token_t self_info;
}node_t;

void add_child(node_t *node, node_t *node_to_add, int index);