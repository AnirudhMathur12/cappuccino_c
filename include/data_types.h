#ifndef DATA_TYPES
#define DATA_TYPES
#include <stdint.h>
#include <stdlib.h>

typedef enum { true = 1, false = 0 } bool;

#define KEYWORD_SIZE 3
#define DATATYPES_SIZE 3
#define COMPARISION_OPERATORS_SIZE 3

static char *keywords[KEYWORD_SIZE] = {"if", "else", "while"};
static char *datatypes[DATATYPES_SIZE] = {"int", "float", "string"};
static char *comparision_operators[COMPARISION_OPERATORS_SIZE] = {">", "<", "=="};

typedef enum {
    TOK_IDENTIFIER,
    TOK_KEYWORD,
    TOK_DATATYPE,
    TOK_NUMBER,
    TOK_LINE_TERMINATOR,
    TOK_CURLY_BRACKETS_START,
    TOK_CURLY_BRACKETS_END,
    TOK_SPECIAL_SYMBOLS,
    TOK_COMPARISION_OPERATOR,
    TOK_PARENTHESES_START,
    TOK_PARENTHESES_END
} TokenType;

typedef struct {
    TokenType type;
    char *token_name;
} Token;

typedef enum {
    INT,
    FLOAT,
    CHAR,
} Datatype;

typedef struct {
    Datatype type;
    char *variable_name;
    uint32_t stack_offset;
} Variable;

typedef struct ASTNode ASTNode;
typedef struct ASTNodeArray ASTNodeArray;

struct ASTNode {
    enum { INTEGER, ADDITION, SUBTRACTION, VARIABLE, ASSIGNMENT, WHILE_LOOP, CONDITIONAL } type;

    union {
        struct {
            int data;
        } INTEGER;
        struct {
            ASTNode *node1;
            ASTNode *node2;
        } ADDITION;
        struct {
            ASTNode *node1;
            ASTNode *node2;
        } SUBTRACTION;
        struct {
            int index;
        } VARIABLE;
        struct {
            int index;
            ASTNode *node;
        } ASSIGNMENT;
        struct {
            ASTNode *condition;
            ASTNodeArray *content;
        } WHILE_LOOP;
        struct {
            enum { GREATER, LESSER, EQUAL } type;
            ASTNode *node1;
            ASTNode *node2;
        } CONDITIONAL;
    } data;
};

ASTNode *ast_new(ASTNode ast);

#define AST_NEW(type, ...) ast_new((ASTNode){type, {.type = {__VA_ARGS__}}})

typedef struct {
    uint32_t length;
    uint32_t capacity;
    Variable *array;
    uint32_t total_stack_space;
} VariableArray;

VariableArray VariableArray_init(int capacity);

typedef struct {
    uint32_t length;
    uint32_t capacity;
    Token *array;
} TokenArray;

TokenArray TokenArray_init(int capacity);

typedef struct {
    uint32_t length;
    uint32_t capacity;
    TokenArray *array;
} Statements;

Statements Statements_init(int capacity);

struct ASTNodeArray {
    uint32_t length;
    uint32_t capacity;
    ASTNode **array;
};

ASTNodeArray ASTNodeArray_init(int capacity);

typedef struct {
    ASTNodeArray astNodeArr;
    VariableArray varArr;
} AbstractSyntaxTree;

AbstractSyntaxTree AST_init(int ast_capacity, int var_capacity);

#endif
