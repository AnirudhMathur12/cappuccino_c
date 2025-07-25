#include "ast.h"
#include "data_types.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define OPSIZE 5
const char *priority[OPSIZE] = {"=", "<", ">", "+", "-"};

ASTNode *form_tree(int start_index, int end_index, TokenArray *arr,
                   int op_index, VariableArray *var_arr);

Statements GenerateStatements(TokenArray tok_arr) {
    Statements statements = Statements_init(128);

    statements.array[statements.length] = TokenArray_init(8);
    TokenArray arr = TokenArray_init(8);
    for (int i = 0; i < tok_arr.length; i++) {
        if (tok_arr.array[i].type == TOK_LINE_TERMINATOR ||
            tok_arr.array[i].type == TOK_PARENTHESES_START ||
            tok_arr.array[i].type == TOK_PARENTHESES_END) {
            statements.array[statements.length++] = arr;
            if (statements.length == statements.capacity - 1) {
                statements.capacity = (int)(statements.capacity * 2.5);
                statements.array = realloc(
                    statements.array, statements.capacity * sizeof(TokenArray));
            }
            arr = TokenArray_init(8);
            continue;
        }
        // arr.array[arr.length].type = tok_arr.array[i].type;
        // arr.array[arr.length].token_name =
        // malloc(strlen(tok_arr.array[i].token_name) + 1);
        // strcpy(arr.array[arr.length].token_name,
        // tok_arr.array[i].token_name);
        // arr.array[arr.length].token_name[strlen(tok_arr.array[i].token_name)]
        // = '\0';
        arr.array[arr.length++] = tok_arr.array[i];
        if (arr.length == arr.capacity - 1) {
            arr.capacity = (int)(arr.capacity * 2.5);
            arr.array = realloc(arr.array, arr.capacity * sizeof(Token));
        }
    }

    if (arr.length > 0) {
        statements.array[statements.length++] = arr;
        if (statements.length == statements.capacity - 1) {
            statements.capacity = (int)(statements.capacity * 2.5);
            statements.array = realloc(
                statements.array, statements.capacity * sizeof(TokenArray));
        }
    }

    return statements;
}

AbstractSyntaxTree GenerateAbstractSyntaxTree(Statements statements) {
    AbstractSyntaxTree ast = AST_init(128, 128);
    VariableArray *var_arr = &ast.varArr;
    ASTNodeArray *ast_arr = &ast.astNodeArr;

    for (int i = 0; i < statements.length; i++) {
        TokenArray *arr = &statements.array[i];
        if (arr->length == 2 && arr->array[0].type == TOK_DATATYPE &&
            arr->array[1].type == TOK_IDENTIFIER) {

            var_arr->array[var_arr->length] = (Variable){
                .type = assignDataType(arr->array[0].token_name),
                .variable_name = arr->array[1].token_name,
            };

            var_arr->array[var_arr->length].stack_offset =
                (var_arr->length)
                    ? (var_arr->array[var_arr->length - 1].stack_offset +
                       determine_size(var_arr->array[var_arr->length].type))
                    : 0,
            var_arr->total_stack_space +=
                determine_size(var_arr->array[var_arr->length].type);
            var_arr->length++;
            // printf("%d\n", var_arr->array[var_arr->length - 1].stack_offset +
            // assignDataType(arr->array[0].token_name));

        } else {
            ast_arr->array[ast_arr->length++] =
                form_tree(0, arr->length, arr, 0, var_arr);
        }
        if (ast_arr->length == ast_arr->capacity - 1) {
            ast_arr->capacity *= 2.5;
            ast_arr->array =
                realloc(ast_arr->array, ast_arr->capacity * sizeof(ASTNode *));
        }
    }
    return ast;
}

ASTNode *form_tree(int start_index, int end_index, TokenArray *arr,
                   int op_index, VariableArray *var_arr) {
    for (int iter = op_index; iter < OPSIZE; iter++) {
        for (int i = start_index; i < end_index; i++) {
            if ((arr->array[i].type == TOK_SPECIAL_SYMBOLS ||
                 arr->array[i].type == TOK_COMPARISION_OPERATOR) &&
                !strcmp(arr->array[i].token_name, priority[iter])) {
                char *op = arr->array[i].token_name;
                if (!strcmp(op, "=")) {
                    return AST_NEW(
                        ASSIGNMENT,
                        assignIndex(arr->array[i - 1].token_name, var_arr),
                        form_tree(i + 1, end_index, arr, iter, var_arr));
                }
                if (!strcmp(op, "+")) {
                    return AST_NEW(
                        ADDITION, form_tree(start_index, i, arr, iter, var_arr),
                        form_tree(i + 1, end_index, arr, iter, var_arr));
                }
                if (!strcmp(op, "-")) {
                    return AST_NEW(
                        SUBTRACTION,
                        form_tree(start_index, i, arr, iter, var_arr),
                        form_tree(i + 1, end_index, arr, iter, var_arr));
                }
            }
        }
    }
    for (int i = start_index; i < end_index; i++) {
        if (arr->array[i].type == TOK_KEYWORD) {
            // if(arr->array[i].token_name == "if") {
            //     return AST_NEW
            // }
        }
        if (arr->array[i].type == TOK_NUMBER) {
            return AST_NEW(INTEGER, atoi(arr->array[i].token_name));
        }
        if (arr->array[i].type == TOK_IDENTIFIER) {
            return AST_NEW(VARIABLE,
                           assignIndex(arr->array[i].token_name, var_arr));
        }
    }
}

int assignIndex(char *name, VariableArray *var_arr) {
    for (int i = 0; i < var_arr->length; i++) {
        if (!strcmp(name, var_arr->array[i].variable_name))
            return i;
    }
    THROW_ERR("The identifier %s has not been defined\n", name);
    return -1;
}

Datatype assignDataType(char *dt) {
    if (!strcmp(dt, "int"))
        return INT;
    else if (!strcmp(dt, "float"))
        return FLOAT;
    else if (!strcmp(dt, "char"))
        return CHAR;
    return -1;
}

int determine_size(Datatype dt) {
    switch (dt) {
    case INT:
        return 32;
    case FLOAT:
        return 32;
    case CHAR:
        return 1;
    }
}
