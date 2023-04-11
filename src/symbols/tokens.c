#include "tokens.h"
#include <stdio.h>  
#include <string.h>

// Operation tokens

char * jmp_ir_base =                    "JUMP";
char * mov_ir_base =                    "MOVE";
char * nop_ir_base =                    "NOP";
char * ret_ir_base =                    "RETURN";
char * push_ir_base =                   "PUSH";
char * pop_ir_base =                    "POP";
char * int_ir_base =                    "INTERRUPT";

// Argument Bases

char * lit_ir_base =                    "LITERAL";
char * reg_ir_base =                    "REGISTER";

// Misc Bases

char * label_ir_base =                  "LABEL";


// General details

char * reference_ir_detail =            "REFERENCE";

// Register types

char * reg_ir_detail_a =                "AREGISTER";
char * reg_ir_detail_b =                "BREGISTER";
char * reg_ir_detail_c =                "CREGISTER";
char * reg_ir_detail_d =                "DREGISTER";
char * reg_ir_detail_src =              "SOURCEREGISTER";
char * reg_ir_detail_dest =             "DESTREGISTER";
char * reg_ir_detail_base =             "STACKBASEPTRREGISTER";
char * reg_ir_detail_stack =            "STACKPTRREGISTER";

// Register size

char * reg_ir_detail_size_8h =          "REGISTERSIZE8HIGH";
char * reg_ir_detail_size_8l =          "REGISTERSIZE8LOW";
char * reg_ir_detail_size_16 =          "REGISTERSIZE16";
char * reg_ir_detail_size_32 =          "REGISTERSIZE32";

// Operation size
char * op_ir_detail_size_byte =         "OPERATIONSIZEBYTE";
char * op_ir_detail_size_word =         "OPERATIONSIZEWORD";
char * op_ir_detail_size_double =       "OPERATIONSIZEDOUBLEWORD";
char * op_ir_detail_size_quad =         "OPERATIONSIZEQUAD";

char **get_token_base_list() {
    return (char*[]) {

/*Operation bases*/     jmp_ir_base, mov_ir_base, nop_ir_base, ret_ir_base, push_ir_base, pop_ir_base, int_ir_base,

/*Argument bases*/      lit_ir_base, reg_ir_base,

/*Misc bases*/          label_ir_base

};
}

char **get_token_detail_list() {
    return (char*[]) {

/*Standard details*/    reference_ir_detail, 

/*Register types*/      reg_ir_detail_a, reg_ir_detail_b, reg_ir_detail_c, reg_ir_detail_d,
                        reg_ir_detail_src, reg_ir_detail_dest, reg_ir_detail_base, reg_ir_detail_stack,

/*Register Sizes*/      reg_ir_detail_size_8h, reg_ir_detail_size_8l, reg_ir_detail_size_16, reg_ir_detail_size_32,

/*Operation sizes*/     op_ir_detail_size_byte, op_ir_detail_size_word, op_ir_detail_size_double, op_ir_detail_size_quad
};
}


void print_token(token_t tok) {
    printf("%s( ", tok.base);
    if (strcmp(tok.details.ident, "") != 0) {
        printf("%s ", tok.details.ident);
    }
    if (strcmp(tok.details.regtype, "") != 0) {
        printf("%s ", tok.details.regtype);
    }
    if (strcmp(tok.details.regsize, "") != 0) {
        printf("%s ", tok.details.regsize);
    }
    if (strcmp(tok.details.general, "") != 0) {
        printf("%s ", tok.details.general);
    }
    if (strcmp(tok.details.opsize, "") != 0) {
        printf("%s ", tok.details.opsize);
    }
    printf(") ");
}