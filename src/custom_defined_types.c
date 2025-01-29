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
    int32_t length;
    int32_t capacity;
    Token *array;
} TokenArray;

void TokenArray_free(TokenArray *tok_arr) {
    free(tok_arr->array);
    free(tok_arr);
}

TokenArray TokenArray_init(int capacity) {
    TokenArray arr = {.length = 0,
                      .capacity = capacity,
                      .array = calloc(arr.capacity, sizeof(Token))};
    return arr;
}

typedef struct {
    TokenArray *statements;
    int size;
    int capacity;
} Scope;

#endif
