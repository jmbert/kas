#pragma once

typedef struct __Macro {
    char *ident;
    char *replace;
    int *references;
    int ref_count;
}macro_t;