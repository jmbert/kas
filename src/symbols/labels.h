#pragma once


typedef struct __Label {
    char *ident;
    int bin_offset;
}label_t;

void add_label(label_t label);

label_t *get_labels();

int get_label_count();

int get_label_offset(char *ident);