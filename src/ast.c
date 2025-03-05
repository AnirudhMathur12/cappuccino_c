#include "ast.h"
#include "data_types.h"
#include <string.h>

Statements GenerateStatements(TokenArray tok_arr) {
    Statements statements = Statements_init(128);

    statements.array[statements.length] = TokenArray_init(8);
    TokenArray *curr = &statements.array[statements.length];
    for (int i = 0; i < tok_arr.length; i++) {
        if (tok_arr.array[i].type == TOK_LINE_TERMINATOR) {
            statements.array[++statements.length] = TokenArray_init(8);
            if (statements.length == statements.capacity - 1) {
                statements.capacity = (int)(statements.capacity * 2.5);
                statements.array = realloc(statements.array, statements.capacity);
            }
            curr = &statements.array[statements.length];
            continue;
        }
        curr->array[curr->length++] = tok_arr.array[i];
        if (curr->length == curr->capacity - 1) {
            curr->capacity = (int)(curr->capacity * 2.5);
            curr->array = realloc(curr->array, curr->capacity);
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
        if (arr->length == 2 &&
            arr->array[0].type == TOK_DATATYPE &&
            arr->array[1].type == TOK_IDENTIFIER) {
            var_arr->array[var_arr->length++] = (Variable){
                .type = assignDataType(arr->array[0].token_name),
                .variable_name = arr->array[1].token_name,
                .stack_offset = (var_arr->length - 1) ? var_arr->array[var_arr->length - 1].stack_offset + assignDataType(arr->array[0].token_name) : 0,
            };
        } else if (arr->length == 3 &&
                   arr->array[0].type == TOK_IDENTIFIER &&
                   arr->array[2].type == TOK_NUMBER &&
                   !strcmp(arr->array[1].token_name, "=")) {
            ast_arr->array[ast_arr->length++] = (ASTNode){
                .type = VAR_ASSIGNMENT,
                .data.VAR_ASSIGNMENT = {
                    .index = assignIndex(arr->array[0].token_name, var_arr),
                    .data = atoi(arr->array[2].token_name),
                },
            };
        }
    }
    return ast;
}

int assignIndex(char *name, VariableArray *var_arr) {
    for (int i = 0; i < var_arr->length; i++) {
        if (!strcmp(name, var_arr->array[i].variable_name))
            return i;
    }
}

Datatype assignDataType(char *dt) {
    if (!strcmp(dt, "int"))
        return INT;
    else if (!strcmp(dt, "float"))
        return FLOAT;
    else if (!strcmp(dt, "char"))
        return CHAR;
}
