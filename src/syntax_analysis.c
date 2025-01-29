#ifndef SYNTAX_ANALYSIS
#define SYNTAX_ANALYSIS
#include "custom_defined_types.c"
#include <stdint.h>
#include <stdio.h>

Statements analyze_statements(TokenArray tok_arr) {
    Statements global_scope = {.capacity = 128, .size = 0};
    global_scope.statements = calloc(global_scope.capacity, sizeof(TokenArray));
    int statement_size = 0;
    for (int i = 0; i < tok_arr.length; i++) {
        if (tok_arr.array[i].type == TOK_LINE_TERMINATOR) {
            global_scope.statements[global_scope.size] = TokenArray_init(statement_size);
            statement_size = 0;
            global_scope.size++;
            if (global_scope.size == global_scope.capacity - 1) {
                global_scope.capacity = (int)(global_scope.capacity * 2.5);
                global_scope.statements = realloc(global_scope.statements,
                                                  (int)sizeof(TokenArray) * global_scope.capacity);
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

AST generate_AST(Statements statements) {
    AST ast = {.capacity = statements.capacity, .length = statements.size};
    ast.array = calloc(ast.capacity, sizeof(ASTNode));
    for (int i = 0; i < statements.size; i++) {
        if (statements.statements[i].length == 2) {
            if (statements.statements[i].array[0].type == TOK_DATATYPE &&
                statements.statements[i].array[1].type == TOK_IDENTIFIER) {
                ast.array[i] = (ASTNode){
                    .type = VAR_DECL,
                    .data = {.VAR_DECL = {.data_type = statements.statements[i].array[0],
                                          .identifier = statements.statements[i].array[1]}}};
            }
        } else if (statements.statements[i].length == 3) {
            if (statements.statements[i].array[0].type == TOK_IDENTIFIER &&
                statements.statements[i].array[1].token_name[0] == '=' &&
                statements.statements[i].array[2].type == TOK_NUMBER) {
                ast.array[i] = (ASTNode){
                    .type = VAR_ASSIGMENT,
                    .data = {.VAR_ASSIGMENT = {.identifier = statements.statements[i].array[0],
                                               .value = statements.statements[i].array[2]}}};
            }
        }
    }

    return ast;
}

#endif
