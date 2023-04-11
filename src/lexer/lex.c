#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "lex.h"
#include "../symbols/tokens.h"


token_t get_register(char *ident) {
    token_t tok;

    char *size;
    char *type;


    tok.base = malloc(sizeof(char)*200);
    

    strcpy(tok.base, get_token_base_list()[8]);

    if (ident[0] == 'e') {
        size = get_token_detail_list()[12];
        if (ident[2] == 'x') {
            if (ident[1] == 'a') {
                type = get_token_detail_list()[1];
            } else if (ident[1] == 'b') {
                type = get_token_detail_list()[2];
            } else if (ident[1] == 'c') {
                type = get_token_detail_list()[3];
            } else if (ident[1] == 'd') {
                type = get_token_detail_list()[4];
            }
        } else {
            if (ident[1] == 'd') {
                type = get_token_detail_list()[6];
            } else if (ident[1] == 'b') {
                type = get_token_detail_list()[7];
            } else if (ident[1] == 's') {
                if (ident[2] == 'p') {
                    type = get_token_detail_list()[8];
                } else {
                    type = get_token_detail_list()[5];
                }
            }
        }
    } else if (ident[1] == 'x') {
        size = get_token_detail_list()[11];
        if (ident[0] == 'a') {
            type = get_token_detail_list()[1];
        } else if (ident[0] == 'b') {
            type = get_token_detail_list()[2];
        } else if (ident[0] == 'c') {
            type = get_token_detail_list()[3];
        } else if (ident[0] == 'd') {
            type = get_token_detail_list()[4];
        }
    } else if (ident[1] == 'h') {
        size = get_token_detail_list()[9];
        if (ident[0] == 'a') {
            type = get_token_detail_list()[1];
        } else if (ident[0] == 'b') {
            type = get_token_detail_list()[2];
        } else if (ident[0] == 'c') {
            type = get_token_detail_list()[3];
        } else if (ident[0] == 'd') {
            type = get_token_detail_list()[4];
        }
    } else {
        size = get_token_detail_list()[10];
        if (ident[0] == 'a') {
            type = get_token_detail_list()[1];
        } else if (ident[0] == 'b') {
            type = get_token_detail_list()[2];
        } else if (ident[0] == 'c') {
            type = get_token_detail_list()[3];
        } else if (ident[0] == 'd') {
            type = get_token_detail_list()[4];
        }
    } 

    tok.details = (tok_details_t){"", type, size, "", ""};
    return tok;
}

token_t get_token(char *ident) {
    token_t tok;

    if (strcmp(ident, "ah") == 0 || strcmp(ident, "al") == 0 || strcmp(ident, "bh") == 0 || strcmp(ident, "bl") == 0 || strcmp(ident, "ch") == 0 || strcmp(ident, "cl") == 0 || strcmp(ident, "dh") == 0 || strcmp(ident, "dl") == 0 || 
        strcmp(ident, "ax") == 0 || strcmp(ident, "bx") == 0 || strcmp(ident, "cx") == 0 || strcmp(ident, "dx") == 0 || 
        strcmp(ident, "eax") == 0 || strcmp(ident, "ebx") == 0 || strcmp(ident, "ecx") == 0 || strcmp(ident, "edx") == 0 ||
        strcmp(ident, "esi") == 0 || strcmp(ident, "edi") == 0 || strcmp(ident, "ebp") == 0 || strcmp(ident, "esp") == 0 ) {

        tok = get_register(ident);
    } else if (strcmp(ident, "jmp") == 0) {
        tok.base = get_token_base_list()[0];
        tok.details = (tok_details_t){"", "", "", "", ""};
    } else if (ident[0] == 'm' && ident[1] == 'o' && ident[2] == 'v') {
        tok.base = get_token_base_list()[1];
        char *size;
        switch (ident[3])
        {
        case 'b':
            size = get_token_detail_list()[13];
            break;
        case 'w':
            size = get_token_detail_list()[14];
            break;
        case 'd':
            size = get_token_detail_list()[15];
            break;
        case 'q':
            size = get_token_detail_list()[16];
            break;
        }
        tok.details = (tok_details_t){"", "", "", "", size};
    } else if (strcmp(ident, "nop") == 0) {
        tok.base = get_token_base_list()[2];
        tok.details = (tok_details_t){"", "", "", "", ""};
    } else if (strcmp(ident, "ret") == 0) {
        tok.base = get_token_base_list()[3];
        tok.details = (tok_details_t){"", "", "", "", ""};
    } else if (ident[0] == 'p' && ident[1] == 'u' && ident[2] == 's' && ident[3] == 'h') {
        tok.base = get_token_base_list()[4];
        char *size;
        switch (ident[4])
        {
        case 'b':
            size = get_token_detail_list()[13];
            break;
        case 'w':
            size = get_token_detail_list()[14];
            break;
        case 'd':
            size = get_token_detail_list()[15];
            break;
        case 'q':
            size = get_token_detail_list()[16];
            break;
        }
        tok.details = (tok_details_t){"", "", "", "", size};
    } else if (ident[0] == 'p' && ident[1] == 'o' && ident[2] == 'p') {
        tok.base = get_token_base_list()[5];
        char *size;
        switch (ident[3])
        {
        case 'b':
            size = get_token_detail_list()[13];
            break;
        case 'w':
            size = get_token_detail_list()[14];
            break;
        case 'd':
            size = get_token_detail_list()[15];
            break;
        case 'q':
            size = get_token_detail_list()[16];
            break;
        }
        tok.details = (tok_details_t){"", "", "", "", size};
    } else if (ident[strlen(ident)-1] == ':') {
        char *temp = (char*)malloc(sizeof(ident));
        strcpy(temp, ident);
        temp[strlen(ident)-1] = '\0';
        tok.base = get_token_base_list()[9];
        tok.details = tok.details = (tok_details_t){"", "", "", "", ""};
        tok.details.ident = (char*)malloc(sizeof(temp));
        strcpy(tok.details.ident, temp);
        free(temp);

    } else if (strcmp(ident, "int") == 0) {
        tok.base = get_token_base_list()[6];
        tok.details = (tok_details_t){"", "", "", "", ""};
    } else {
        tok.base = get_token_base_list()[7];
        tok.details = (tok_details_t){"", "", "", "", ""};
        tok.details.ident = (char*)malloc(sizeof(ident));
        strcpy(tok.details.ident, ident);
    }
    return tok;
}

void scan_word(char *buffer, char *src, int *index) {
    for (;src[*index] != '\0' && src[*index] != ' ' && src[*index] != '\n' && src[*index] != '\t'; (*index)++) {
        strncat(buffer, &src[*index], 1);
    }
}

void scan_ws(char *src, int *index) {
    for (;src[*index] != '\0' && (src[*index] == ' ' || src[*index] == '\n' || src[*index] == '\t'); (*index)++) {
    }
}

token_t *lex(char *source) {
    token_t *tokens = (token_t*)malloc(sizeof(token_t)*2000);
    

    char *buffer = (char*)malloc(sizeof(char)*2000);
    *buffer = '\0';

    int count = 0;

    for (int i = 0; source[i] != '\0'; i++) {
        if (source[i] == ' ' || source[i] == '\n' || source[i] == '\t') {
            scan_ws(source, &i);
        }
        scan_word(buffer, source, &i);
        token_t tok = get_token(buffer);
        tokens[count] = tok;
        *buffer = '\0';
        count++;
    }

    return tokens;
}