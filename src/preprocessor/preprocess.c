#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "preprocess.h"
#include "../symbols/macros.h"

macro_t *macros;

unsigned int macro_count;

void get_arg(char *source, char *buffer, int *index, char delim) {
    for (; source[*index] != '\n' && source[*index] != '\0'; (*index)++)
    {
        if (source[*index] == delim) {
            (*index)++;
            break;
        } 
        strncat(buffer, &source[*index], 1);
    }

    for (int macro_index = 0; macro_index < macro_count; macro_index++) {
        if (strcmp(buffer, macros[macro_index].ident) == 0) {
            strcpy(buffer, macros[macro_index].replace);
        }
    }
    
}

void get_macro_references(char *src, macro_t *macro, unsigned int current_position) {
    
    int *references = (int*)malloc(sizeof(int)*2000);

    int count = 0;
    char *tmp = src+current_position;
    while( tmp = strstr( tmp, macro->ident)){
        references[count] = (int)(tmp-src);
        tmp++;
        count++;
    }
    
    macro->references = references;
    macro->ref_count = count;
}

char *preprocess_parse_directive(int *index, char *source) {
    (*index)++;

    char *cmd = (char*)malloc(sizeof(char)*2000);
    *cmd = '\0';

    get_arg(source, cmd, index, ' ');

    if (strcmp(cmd, "define") == 0) {
        char *ident = (char*)malloc(sizeof(char)*2000);
        *ident = '\0';
        
        get_arg(source, ident, index, ' ');

        char *replace = (char*)malloc(sizeof(char)*2000);
        *replace = '\0';
        get_arg(source, replace, index, '\n');
        
        macro_t macro;
        macro.ident = (char*)malloc(sizeof(char)*2000);
        macro.replace = (char*)malloc(sizeof(char)*2000);
        strcpy(macro.ident, ident);
        strcpy(macro.replace, replace);
        get_macro_references(source, &macro, *index);
        macros[macro_count] = macro;
        macro_count++;
    } else if (strcmp(cmd, "include") == 0) {
        char *path = (char*)malloc(sizeof(char)*2000);
        *path = '\0';
        
        get_arg(source, path, index, '\n');

        FILE *file = fopen(path, "r");

        char *file_contents = malloc(sizeof(char)*20000);

        long length;

        if (file) {

            fseek (file, 0, SEEK_END);
            length = ftell (file);
            fseek (file, 0, SEEK_SET);
            file_contents = malloc (length+1);

            if (file_contents) {
                fread(file_contents, 1, length, file);
            }

            fclose (file);
        }

        return file_contents;

        free(path);
    
    }

    free(cmd);

    return NULL;
}

char *preprocess(char *src_contents) {
    macros = (macro_t*)malloc(sizeof(macro_t)*2000);

    char *preprocessed_source = (char*)malloc(sizeof(char)*2000);

    strcat(preprocessed_source, "\n");

    for (int i = 0; src_contents[i] != '\0'; i++) {

        for (int macro_index = 0; macro_index < macro_count; macro_index++) {
            for (int ref_index = 0; ref_index < macros[macro_index].ref_count; ref_index++) {
                if (i == macros[macro_index].references[ref_index]) {
                    strcat(preprocessed_source, macros[macro_index].replace);
                    i += strlen(macros[macro_index].ident);
                }
            }
        }

        if (i == 0) {
            if (src_contents[i] == '%') {
                char *directive_return = preprocess_parse_directive(&i, src_contents);
                if (directive_return != NULL) {
                    strcat(preprocessed_source, directive_return);
                    free(directive_return);
                }
            } 
        }
        
        if (src_contents[i] == '\n') {
            
            if (src_contents[i+1] == '%') {
                strncat(preprocessed_source, &src_contents[i], 1);
                i++;
                char *directive_return = preprocess_parse_directive(&i, src_contents);
                i--;
                if (directive_return != NULL) {
                    strcat(preprocessed_source, directive_return);
                    free(directive_return);
                }

            } else {
                strncat(preprocessed_source, &src_contents[i], 1);
            }
        } else if (src_contents[i] == ';') {
            for (;src_contents[i] != '\n';i++);
            i--;
        } else {
            strncat(preprocessed_source, &src_contents[i], 1);
        }
        
    }

    strcat(preprocessed_source, "\n");

    return preprocessed_source;
}