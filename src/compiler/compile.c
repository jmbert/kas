#include "compile.h"
#include <stdio.h>
#include "../symbols/ast.h"
#include "../symbols/tokens.h"
#include "../symbols/labels.h"
#include <stdlib.h>
#include <string.h>

int get_instruction_byte(node_t *node, int *current_bin_pos, int *bytes) {
    if (strcmp(node->self_info.base, get_token_base_list()[0]) == 0) {

    } else if (strcmp(node->self_info.base, get_token_base_list()[1]) == 0) {

    } else if (strcmp(node->self_info.base, get_token_base_list()[2]) == 0) {
        (*current_bin_pos)++;
        (*bytes) = 1;
        return 0x90;
    } else if (strcmp(node->self_info.base, get_token_base_list()[3]) == 0) {
        if (node->child_count) {
            (*current_bin_pos)+=2;
            (*bytes) = 2;
            return (0xc2 << 8) + get_instruction_byte(node->children[0], current_bin_pos, bytes);
        } else {
            (*current_bin_pos)++;
            (*bytes) = 1;
            return 0xc3;
        }

    } else if (strcmp(node->self_info.base, get_token_base_list()[4]) == 0) {

    } else if (strcmp(node->self_info.base, get_token_base_list()[5]) == 0) {

    } else if (strcmp(node->self_info.base, get_token_base_list()[6]) == 0) {
        if (!strcmp(node->children[0]->self_info.base, get_token_base_list()[7])) {
            (*current_bin_pos)+=2;
            (*bytes) = 2;
            return (0xcd << 8) + get_instruction_byte(node->children[0], current_bin_pos, bytes);
            
        } else {
            printf("Expected literal argument for int, got %s\n", node->children[0]->self_info.base);
            exit(-1);
        }

    } else if (strcmp(node->self_info.base, get_token_base_list()[7]) == 0) {

        int l_offset = get_label_offset(node->self_info.details.ident);

        if (l_offset != -1) {
            return l_offset;
        }

        return strtol(node->self_info.details.ident, NULL, 0);

    } else if (strcmp(node->self_info.base, get_token_base_list()[8]) == 0) {

    } else if (strcmp(node->self_info.base, get_token_base_list()[9]) == 0) {
        label_t this_label;
        this_label.ident = node->self_info.details.ident;
        this_label.bin_offset = *current_bin_pos;
        add_label(this_label);
        return 0;
    }
}

void compile(node_t *ast, FILE *out) {
    unsigned char *buffer = (unsigned char*)malloc(sizeof(unsigned char)*20000);
    for (int i = 0; i < 20000; i++) {
        buffer[i] = 0;
    }



    int bin_pos = 0;
    for (int i = 0; i < ast->child_count; i++) {
        int bytes = 0;
        int b = get_instruction_byte(ast->children[i], &bin_pos, &bytes);

        

        for (int i = 0; i < bytes; i++) {
            buffer[bin_pos-i-1] = (b >> (8*i))%256;
        }
    }
     
    for (int i = 0; i < get_label_count(); i++) {
        printf("Label %s: %d\n", get_labels()[i].ident, get_labels()[i].bin_offset);
    }

    
    
    fwrite(buffer, bin_pos, 1, out);
}