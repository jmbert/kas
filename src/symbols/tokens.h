#pragma once

typedef struct __Token_Detail {
    char *ident;
    char *regtype;
    char *regsize;
    char *general;
    char *opsize;
}tok_details_t;

typedef struct __Token {
    char *base;
    tok_details_t details;
}token_t;

char **get_token_base_list();

char **get_token_detail_list();

void print_token(token_t tok);