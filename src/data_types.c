#include "data_types.h"

TokenArray TokenArray_init(int capacity) {
    return (TokenArray){
        .length = 0, .capacity = capacity, .array = calloc(capacity, sizeof(Token))};
}

ASTNodeArray ASTNodeArray_init(int capacity) {
    return (ASTNodeArray){
        .length = 0, .capacity = capacity, .array = calloc(capacity, sizeof(ASTNode))};
}
