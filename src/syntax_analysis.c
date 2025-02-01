#ifndef SYNTAX_ANALYSIS
#define SYNTAX_ANALYSIS
#include "custom_defined_types.c"
#include <stdint.h>
#include <stdio.h>
#include <string.h>

Statements analyze_statements(TokenArray tok_arr) {
    Statements statements = {.capacity = 128, .size = 0};
    statements.statements = calloc(statements.capacity, sizeof(TokenArray));
    int statement_size = 0;
    for (int i = 0; i < tok_arr.length; i++) {
        if (tok_arr.array[i].type == TOK_LINE_TERMINATOR) {
            statements.statements[statements.size] = TokenArray_init(statement_size);
            statement_size = 0;
            statements.size++;
            if (statements.size == statements.capacity - 1) {
                statements.capacity = (int)(statements.capacity * 2.5);
                statements.statements =
                    realloc(statements.statements, (int)sizeof(TokenArray) * statements.capacity);
            }
        } else {
            statement_size++;
        }
    }

    int arr_iter = 0;
    int statement_iter = 0;
    for (int i = 0; i < tok_arr.length; i++) {
        if (tok_arr.array[i].type == TOK_LINE_TERMINATOR) {
            statements.statements[arr_iter].length = statement_iter;
            arr_iter++;
            statement_iter = 0;
        } else {
            statements.statements[arr_iter].array[statement_iter] = tok_arr.array[i];
            statement_iter++;
        }
    }

    return statements;
}

#endif
