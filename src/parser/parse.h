#pragma once

#include "../symbols/ast.h"
#include "../symbols/tokens.h"

node_t *parse(token_t *tokens);

void free_node(node_t *node);