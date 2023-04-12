#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../preprocessor/preprocess.h"
#include "../lexer/lex.h"
#include "../parser/parse.h"
#include "../compiler/compile.h"
#include "../symbols/tokens.h"
#include "../symbols/ast.h"

int main(int argc, char *argv[]) {

    if (argc < 3) {
        printf("Please provide input and output arguments\n");
        return -1;
    }

    FILE *src = fopen(argv[1], "r");
    FILE *out = fopen(argv[2], "w");

    char *src_contents = "";

    long length;

    if (src) {
        
        fseek (src, 0, SEEK_END);
        length = ftell (src);
        fseek (src, 0, SEEK_SET);
        src_contents = malloc (length+1);

        if (src_contents) {
            fread(src_contents, 1, length, src);
        }

        fclose (src);
    }

    char *preprocessed_src = preprocess(src_contents);
    
    printf("%s\n", preprocessed_src);

    free(src_contents);

    token_t *tokens = lex(preprocessed_src);;
    free(preprocessed_src);

    for (int i = 0; tokens[i].base; i++) {
        token_t tok = tokens[i];
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
    
    printf("\n");

    
    node_t *ast = parse(tokens);

    free(tokens);


    compile(ast, out);

    fclose(out);

    free_node(ast);

    return 0;
}