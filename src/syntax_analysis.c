#ifndef SYNTAX_ANALYSIS
#define SYNTAX_ANALYSIS
#include "tokenizer.c"

typedef struct Instruction Instruction;

typedef struct {
    Instruction *arr;
} Scope;

typedef struct {
    enum { STATEMENT, BLOCK } type;
    union {
        Token *statement;
        Scope *new_scope;
    } data;
} Instruction;

#endif
