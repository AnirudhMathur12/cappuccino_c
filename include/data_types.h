#ifndef DATA_TYPES
#define DATA_TYPES
#include <stdint.h>
#include <stdlib.h>

typedef enum { true = 1, false = 0 } bool;

#define KEYWORD_SIZE 3
#define DATATYPES_SIZE 3

static char *keywords[KEYWORD_SIZE] = {"if", "else", "while"};
static char *datatypes[DATATYPES_SIZE] = {"int", "float", "string"};

typedef enum {
    TOK_IDENTIFIER,
    TOK_KEYWORD,
    TOK_DATATYPE,
    TOK_NUMBER,
    TOK_LINE_TERMINATOR,
    TOK_BRACKETS,
    TOK_SPECIAL_SYMBOLS,
} TokenType;

typedef struct {
    TokenType type;
    char *token_name;
} Token;

typedef struct {
    enum { VAR_DECLARATION, VAR_DEFINITION } type;

    union {
        struct {
            char *identifier_name;
            char *identifier_type;
        } VAR_DECLARATION;

        struct {
            char *identifier_name;
            char *data;
        } VAR_DEFINITION;
    } data;

} ASTNode;

typedef struct {
    uint32_t length;
    uint32_t capacity;
    Token *array;
} TokenArray;

TokenArray TokenArray_init(int capacity);

typedef struct {
    uint32_t length;
    uint32_t capacity;
    ASTNode *array;
} ASTNodeArray;

ASTNodeArray ASTNodeArray_init(int capacity);

#endif
