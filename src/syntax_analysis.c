#ifndef SYNTAX_ANALYSIS
#define SYNTAX_ANALYSIS
#include "custom_defined_types.c"
#include <stdio.h>

Scope *analyze_statements(Token *tok_arr) {
    Scope *global_scope = malloc(sizeof(Scope));
    global_scope->size = 300;
    global_scope->statement_size = calloc(global_scope->size, sizeof(int));
    int iter = 0;
    int statement_size = 0;

    while (tok_arr[iter].type != TOK_ARR_TERMINATE) {
        if (tok_arr[iter].type == TOK_LINE_TERMINATOR) {
            printf("%d\n", statement_size);
            statement_size = 0;
        } else {
            statement_size++;
        }
        iter++;
    }

    return global_scope;
}

#endif
