#ifndef USER_DEFINED_TYPES
#define USER_DEFINED_TYPES
#include <stdint.h>
#include <stdlib.h>

typedef enum { true = 1, false = 0 } bool;

#define KEYWORD_SIZE 3
#define DATATYPES_SIZE 3

char *keywords[KEYWORD_SIZE] = {"if", "else", "while"};
char *datatypes[DATATYPES_SIZE] = {"int", "float", "string"};

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
    char *file_name;
} TokenArray;

TokenArray TokenArray_init(int capacity) {
    return (TokenArray){
        .length = 0, .capacity = capacity, .array = calloc(capacity, sizeof(Token))};
}

#endif
