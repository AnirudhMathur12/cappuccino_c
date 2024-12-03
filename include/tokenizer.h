#ifndef TOKENIZER_H_
#define TOKENIZER_H_
#include "utils.h"
#include <string.h>
enum tokentype
{
    TOK_IDENTIFIER,
    TOK_DATATYPE,
    TOK_CONSTANT,
	TOK_BRACKET,
    TOK_KEYWORD
};

typedef struct
{
    enum tokentype toktype;
    char *tok_name;
} Token;

void printNodeData_Token(void *data);
Token *createToken(enum tokentype _tt, char *tn);

LinkedList *tokenize(char *data);
Token *bufferdump(char *buffer);

int identifytokentype(char *data);

#endif
