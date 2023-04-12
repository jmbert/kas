#include "labels.h"

#include <stdlib.h>
#include <string.h>

label_t *labels;

int labelcount = 0;

void add_label(label_t label) {
    if (labels == NULL) {
        labels = malloc(sizeof(label_t)*2000);
    }
    labels[labelcount] = label;
    labelcount++;
}

label_t *get_labels() {
    return labels;
}

int get_label_offset(char *ident) {
    for (int i = 0; i < labelcount; i++) {
        if (strcmp(labels[i].ident, ident) == 0) {
            return labels[i].bin_offset;
        }
    }

    return -1;
}

int get_label_count() {
    return labelcount;
}