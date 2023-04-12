#pragma once

#include <stdio.h>

#include "../symbols/ast.h"

void compile(node_t *ast, FILE *out);