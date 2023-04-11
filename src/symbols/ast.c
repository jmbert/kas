#include "ast.h"

node_t prog_node;

void add_child(node_t *node, node_t *node_to_add, int index) {
    node->children[index] = node_to_add;
}