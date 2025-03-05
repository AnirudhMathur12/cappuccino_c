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
        .array = calloc(capacity, sizeof(Variable)),
    };
}

ASTNodeArray ASTNodeArray_init(int capacity) {
    return (ASTNodeArray){
        .length = 0,
        .capacity = capacity,
        .array = calloc(capacity, sizeof(ASTNode)),
    };
}

AbstractSyntaxTree AST_init(int ast_capacity, int var_capacity) {
    return (AbstractSyntaxTree){
        .astNodeArr = ASTNodeArray_init(ast_capacity),
        .varArr = VariableArray_init(var_capacity),
    };
}
