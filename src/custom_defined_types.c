#ifndef USER_DEFINED_TYPES
#define USER_DEFINED_TYPES
#include <stdint.h>
#include <stdlib.h>

typedef enum { true = 1, false = 0 } bool;

typedef enum {
    TOK_IDENTIFIER,
    TOK_KEYWORD,
    TOK_DATATYPE,
    TOK_NUMBER,
    TOK_LINE_TERMINATOR,
    TOK_BRACKETS,
    TOK_SPECIAL_SYMBOLS,
    TOK_ARR_TERMINATE
} TokenType;

typedef struct {
    TokenType type;
    char *token_name;
} Token;

typedef struct {
    uint32_t length;
    uint32_t capacity;
    Token *array;
} TokenArray;

void TokenArray_free(TokenArray *tok_arr) {
    free(tok_arr->array);
    free(tok_arr);
}

TokenArray TokenArray_init(int capacity) {
    TokenArray arr = {.length = 0, .capacity = capacity, .array = calloc(arr.capacity, sizeof(Token))};
    return arr;
}

typedef struct {
    TokenArray *statements;
    uint32_t size;
    uint32_t capacity;
} Statements;

typedef struct {
    enum { VAR_DECL, VAR_ASSIGMENT } type;
    union {
        struct {
            Token data_type;
            Token identifier;
        } VAR_DECL;
        struct {
            Token identifier;
            Token value;
        } VAR_ASSIGMENT;
    } data;
} ASTNode;

typedef struct {
    ASTNode *array;
    uint32_t length;
    uint32_t capacity;
} AST;

#endif
