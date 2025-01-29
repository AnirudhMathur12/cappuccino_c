#ifndef SYNTAX_ANALYSIS
#define SYNTAX_ANALYSIS
#include "custom_defined_types.c"
#include <stdint.h>
#include <stdio.h>

Scope analyze_statements(TokenArray tok_arr) {
    Scope global_scope = {.capacity = 128, .size = 0};
    global_scope.statements = calloc(global_scope.capacity, sizeof(TokenArray));
    int statement_size = 0;
    for (int i = 0; i < tok_arr.length; i++) {
        if (tok_arr.array[i].type == TOK_LINE_TERMINATOR) {
            global_scope.statements[global_scope.size] = TokenArray_init(statement_size);
            statement_size = 0;
            global_scope.size++;
            if (global_scope.size == global_scope.capacity - 1) {
                global_scope.capacity = (int)(global_scope.capacity * 2.5);
                global_scope.statements =
                    realloc(global_scope.statements, (int)sizeof(TokenArray) * global_scope.capacity);
            }
        } else {
            statement_size++;
        }
    }

    int arr_iter = 0;
    int statement_iter = 0;
    for (int i = 0; i < tok_arr.length; i++) {
        if (tok_arr.array[i].type == TOK_LINE_TERMINATOR) {
            global_scope.statements[arr_iter].length = statement_iter;
            arr_iter++;
            statement_iter = 0;
        } else {
            global_scope.statements[arr_iter].array[statement_iter] = tok_arr.array[i];
            statement_iter++;
        }
    }

    return global_scope;
}

#endif
