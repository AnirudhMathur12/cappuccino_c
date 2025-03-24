#include "data_types.h"

TokenArray TokenArray_init(int capacity) {
    return (TokenArray){
        .length = 0,
        .capacity = capacity,
        .array = calloc(capacity, sizeof(Token)),
    };
}

Statements Statements_init(int capacity) {
    return (Statements){
        .length = 0,
        .capacity = capacity,
        .array = calloc(capacity, sizeof(TokenArray)),
    };
}

VariableArray VariableArray_init(int capacity) {
    return (VariableArray){
        .length = 0,
        .capacity = capacity,
        .total_stack_space = 0,
        .array = calloc(capacity, sizeof(Variable)),
    };
}

ASTNode *ast_new(ASTNode ast) {
    ASTNode *ptr = malloc(sizeof(ASTNode));
    if (ptr)
        *ptr = ast;

    return ptr;
}

ASTNodeArray ASTNodeArray_init(int capacity) {
    return (ASTNodeArray){
        .length = 0,
        .capacity = capacity,
        .array = calloc(capacity, sizeof(ASTNode *)),
    };
}

AbstractSyntaxTree AST_init(int ast_capacity, int var_capacity) {
    return (AbstractSyntaxTree){
        .astNodeArr = ASTNodeArray_init(ast_capacity),
        .varArr = VariableArray_init(var_capacity),
    };
}
