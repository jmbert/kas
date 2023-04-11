#include "parse.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "../symbols/ast.h"
#include "../symbols/tokens.h"

node_t get_node_from_token_list(token_t *tokens, int *index) {
    printf("Entering parsing of node with token: ");
    print_token(tokens[*index]);
    printf("\n");
    node_t node;
    node.children = (node_t**)malloc(sizeof(node_t*)*10);
    token_t tok = tokens[*index];
    node.self_info = tok;
    if (strcmp(tok.base, get_token_base_list()[0]) == 0) {
        (*index)++;
        node_t *arg = (node_t*)malloc(sizeof(node_t));
        *arg = get_node_from_token_list(tokens, index);
        node.children[0] = arg;
        node.child_count = 1;
        (*index)++;
    } else if (strcmp(tok.base, get_token_base_list()[1]) == 0) {
        (*index)++;

        node_t *arg_1 = (node_t*)malloc(sizeof(node_t));
        *arg_1 = get_node_from_token_list(tokens, index);

        (*index)++;
        node_t *arg_2 = (node_t*)malloc(sizeof(node_t));
        *arg_2 = get_node_from_token_list(tokens, index);

        node_t *tmp = (node_t*)malloc(sizeof(node_t));

        node.children[0] = arg_1;
        node.children[1] = arg_2;
        node.child_count = 2;
        (*index)++;
    } else if (strcmp(tok.base, get_token_base_list()[2]) == 0) {
        (*index)++;
        node.child_count = 0;
    } else if (strcmp(tok.base, get_token_base_list()[3]) == 0) {
        (*index)++;
        node_t *arg = (node_t*)malloc(sizeof(node_t));
        *arg = get_node_from_token_list(tokens, index);
        node.children[0] = arg; 

        (*index)++;
        node.child_count = 1;
    } else if (strcmp(tok.base, get_token_base_list()[4]) == 0) {
        (*index)++;
        node_t *arg = (node_t*)malloc(sizeof(node_t));
        *arg = get_node_from_token_list(tokens, index);
        node.children[0] = arg; 

        (*index)++;
        node.child_count = 1;
    } else if (strcmp(tok.base, get_token_base_list()[5]) == 0) {
        (*index)++;
        node_t *arg = (node_t*)malloc(sizeof(node_t));
        *arg = get_node_from_token_list(tokens, index);
        node.children[0] = arg; 

        (*index)++;
        node.child_count = 1;
    } else if (strcmp(tok.base, get_token_base_list()[6]) == 0) {
        (*index)++;
        node_t *arg = (node_t*)malloc(sizeof(node_t));
        node_t tmp = 
        *arg = get_node_from_token_list(tokens, index);
        
        node.children[0] = arg; 

        (*index)++;
        node.child_count = 1;
    } else {
        node.child_count = 0;
    }

    printf("Exiting parsing of node with token: ");
    print_token(node.self_info);
    printf("\n");
    return node;
}

node_t parse(token_t *tokens) {
    
    node_t ast;

    int j = 0;
    for (int i = 0; tokens[i].base; i++) {
        node_t *node = (node_t*)malloc(sizeof(node_t));
        *node = get_node_from_token_list(tokens, &i);
        ast.children[j] = node;
        j++;
    }
    
    

    return ast;
}