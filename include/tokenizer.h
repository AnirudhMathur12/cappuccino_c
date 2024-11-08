#ifndef TOKENIZER_H_
#define TOKENIZER_H_
#include "utils.h"
enum tokentype
{
    TOK_IDENTIFIER,
    TOK_DATATYPE,
    TOK_CONSTANT
};

typedef struct
{
    enum tokentype toktype;
    char *tok_name;
} Token;

void printNodeData_Token(void *data);
Token *createToken(enum tokentype _tt, char *tn);

#endif
