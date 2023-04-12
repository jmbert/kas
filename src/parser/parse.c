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
    
    token_t tok = tokens[*index];
    node.self_info = tok;
    
    if (strcmp(tok.base, get_token_base_list()[0]) == 0) {
        node.child_count = 1;
        node.children = (node_t**)malloc(sizeof(node_t*)*node.child_count);
        (*index)++;
        node_t *arg = (node_t*)malloc(sizeof(node_t));
        *arg = get_node_from_token_list(tokens, index);
        node.children[0] = arg;
        
    } else if (strcmp(tok.base, get_token_base_list()[1]) == 0) {
        node.child_count = 2;
        node.children = (node_t**)malloc(sizeof(node_t*)*node.child_count);
        (*index)++;

        node_t *arg_1 = (node_t*)malloc(sizeof(node_t));
        *arg_1 = get_node_from_token_list(tokens, index);

        (*index)++;
        node_t *arg_2 = (node_t*)malloc(sizeof(node_t));
        *arg_2 = get_node_from_token_list(tokens, index);

        node_t *tmp = (node_t*)malloc(sizeof(node_t));

        node.children[0] = arg_1;
        node.children[1] = arg_2;

    } else if (strcmp(tok.base, get_token_base_list()[2]) == 0) {
        node.child_count = 0;
    } else if (strcmp(tok.base, get_token_base_list()[3]) == 0) {
        
        if (strcmp(tokens[*index].base, get_token_base_list()[7]) == 0) {
            node.child_count = 1;
            node.children = (node_t**)malloc(sizeof(node_t*)*node.child_count);
            node_t *arg = (node_t*)malloc(sizeof(node_t));
            *arg = get_node_from_token_list(tokens, index);
            node.children[0] = arg; 

            (*index)++;
        } else {
            node.child_count = 0;
        }
        
    } else if (strcmp(tok.base, get_token_base_list()[4]) == 0) {
        node.child_count = 1;
        node.children = (node_t**)malloc(sizeof(node_t*)*node.child_count);
        (*index)++;
        node_t *arg = (node_t*)malloc(sizeof(node_t));
        *arg = get_node_from_token_list(tokens, index);
        node.children[0] = arg; 


    } else if (strcmp(tok.base, get_token_base_list()[5]) == 0) {
        node.child_count = 1;
        node.children = (node_t**)malloc(sizeof(node_t*)*node.child_count);
        (*index)++;
        node_t *arg = (node_t*)malloc(sizeof(node_t));
        *arg = get_node_from_token_list(tokens, index);
        node.children[0] = arg; 

        
    } else if (strcmp(tok.base, get_token_base_list()[6]) == 0) {
        node.child_count = 1;
        node.children = (node_t**)malloc(sizeof(node_t*)*node.child_count);
        (*index)++;
        node_t *arg = (node_t*)malloc(sizeof(node_t));
        node_t tmp = 
        *arg = get_node_from_token_list(tokens, index);
        
        node.children[0] = arg; 

    } else {
        node.child_count = 0;
    }

    

    printf("Exiting parsing of node with token: ");
    print_token(node.self_info);
    printf("\n");
    
    
    
    return node;
}

void free_node(node_t *node) {
    printf("Entering freeing of node with token: ");
    print_token(node->self_info);
    printf("\n");

    if (node->child_count > 0) {
        for (int i = 0; i < node->child_count; i++) {
            free_node(node->children[i]);
        }
    } 
    free(node);

    printf("Exiting freeing of node with token: ");
    print_token(node->self_info);
    printf("\n");
}



node_t *parse(token_t *tokens) {
    
    node_t *ast = (node_t*)malloc(sizeof(node_t));

    ast->self_info.base = "ASTTOP";
    ast->self_info.details = (tok_details_t){"", "", "", "", ""};
    ast->child_count = 0;
    ast->children = (token_t**)malloc(sizeof(token_t*)*2000);
    int j = 0;
    for (int i = 0; tokens[i].base; i++) {
        node_t *node = (node_t*)malloc(sizeof(node_t));
        
        *node = get_node_from_token_list(tokens, &i);
        ast->children[j] = node;
        ast->child_count++;
        j++;
        
    }
    
    

    return ast;
}