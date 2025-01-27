#ifndef TOKENIZER
#define TOKENIZER
#include "utils.c"
#include <stdlib.h>
#include <string.h>

typedef enum {
    TOK_IDENTIFIER,
    TOK_KEYWORD,
    TOK_DATATYPE,
    TOK_NUMBER,
    TOK_SPECIAL_SYMBOLS,
    TOK_ARR_TERMINATE
} TokenType;

typedef struct {
    TokenType type;
    char *token_name;
} Token;

Token *tokenize(char *data);
void buffer_to_token(char *buffer, int iter);

const int KEYWORD_SIZE = 3;
const int DATATYPES_SIZE = 3;

char *keywords[KEYWORD_SIZE] = {"if", "else", "while"};
char *datatypes[DATATYPES_SIZE] = {"int", "float", "string"};

Token *tok_arr;
int current;
int max;

Token *tokenize(char *data) {

    max = 128;
    tok_arr = calloc(max, sizeof(Token));
    current = 0;

    char *buffer = malloc(1024);

    int offset = 0;

    for (int i = 0; i < strlen(data); i++) {
        if (ISALPHA(data[i]) || ISNUM(data[i])) {
            buffer[i - offset] = data[i];
        } else {
            buffer[i - offset] = '\0';
            buffer_to_token(buffer, current);
            current++;
            offset = i;
            if (!ISWHITESPACE(data[i])) {
                buffer[i - offset] = data[i];
                buffer[i - offset + 1] = '\0';
                buffer_to_token(buffer, current);
                current++;
            }
            offset = i + 1;
        }

        if (current == max - 1) {
            max = (int)(max * 2.5);
            realloc(tok_arr, (int)max);
        }
    }
    tok_arr[current++] = (Token){.token_name = NULL, .type = TOK_ARR_TERMINATE};
    free(buffer);
    return tok_arr;
}

void buffer_to_token(char *buffer, int iter) {
    // printf("%s\t", buffer);
    tok_arr[iter].token_name = malloc(strlen(buffer) + 1);
    strcpy(tok_arr[iter].token_name, buffer);

    for (int i = 0; i < KEYWORD_SIZE; i++) {
        if (!strcmp(buffer, keywords[i])) {
            tok_arr[iter].type = TOK_KEYWORD;
            return;
        }
    }
    for (int i = 0; i < DATATYPES_SIZE; i++) {
        if (!strcmp(buffer, datatypes[i])) {
            tok_arr[iter].type = TOK_DATATYPE;
            return;
        }
    }
    bool pure_number = true;
    for (int i = 0; i < strlen(buffer); i++) {
        if (!ISNUM(buffer[i])) {
            pure_number = false;
        }
    }
    if (pure_number) {
        tok_arr[iter].type = TOK_NUMBER;
    }

    tok_arr[iter].type = TOK_IDENTIFIER;
    // printf("%d\n", tok_arr[iter].type);
    return;
}
#endif
