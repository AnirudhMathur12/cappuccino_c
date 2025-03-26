#include "tokenizer.h"
#include "data_types.h"
#include "utils.h"

TokenArray tok_arr;
int current;
// int max;

TokenArray tokenize(char *data, char *file_name) {

    tok_arr = TokenArray_init(10);
    current = 0;

    char *buffer = calloc(1024, 1);

    int offset = 0;

    for (int i = 0; i < strlen(data); i++) {
        if (ISALPHA(data[i]) || ISNUM(data[i])) {
            buffer[i - offset] = data[i];
        } else {
            buffer[i - offset] = '\0';
            if (strlen(buffer)) {
                buffer_to_token(buffer);
                tok_arr.length++;
                current++;
                offset = i;
            }
            if (!ISWHITESPACE(data[i])) {
                buffer[i - offset] = data[i];
                buffer[i - offset + 1] = '\0';
                buffer_to_token(buffer);
                tok_arr.length++;
                current++;
            }
            offset = i + 1;
        }

        if (current == tok_arr.capacity - 1) {
            tok_arr.capacity = (int)(tok_arr.capacity * 2.5);
            tok_arr.array = realloc(tok_arr.array, (int)tok_arr.capacity * sizeof(Token));
            // printf("Updated token array to size %d\n", tok_arr.capacity);
        }
    }
    free(buffer);
    return tok_arr;
}

void buffer_to_token(char *buffer) {
    // printf("%s.\n", buffer);
    tok_arr.array[tok_arr.length].token_name = malloc(strlen(buffer) + 1);
    strcpy(tok_arr.array[tok_arr.length].token_name, buffer);

    for (int i = 0; i < KEYWORD_SIZE; i++) {
        // printf("Comparing %s with %s\n", buffer, keywords[i]);
        if (!strcmp(buffer, keywords[i])) {
            tok_arr.array[tok_arr.length].type = TOK_KEYWORD;
            return;
        }
    }
    for (int i = 0; i < DATATYPES_SIZE; i++) {
        if (!strcmp(buffer, datatypes[i])) {
            tok_arr.array[tok_arr.length].type = TOK_DATATYPE;
            return;
        }
    }
    bool pure_number = true;
    for (int i = 0; i < strlen(buffer); i++) {
        if (!ISNUM(buffer[i])) {
            pure_number = false;
            break;
        }
    }
    if (pure_number) {
        tok_arr.array[tok_arr.length].type = TOK_NUMBER;
        return;
    }

    if (buffer[0] == '{') {
        tok_arr.array[tok_arr.length].type = TOK_CURLY_BRACKETS_START;
        return;
    }

    if (buffer[0] == '}') {
        tok_arr.array[tok_arr.length].type = TOK_CURLY_BRACKETS_END;
        return;
    }

    if (buffer[0] == '(') {
        tok_arr.array[tok_arr.length].type = TOK_PARENTHESES_START;
        return;
    }

    if (buffer[0] == ')') {
        tok_arr.array[tok_arr.length].type = TOK_PARENTHESES_END;
        return;
    }

    if (buffer[0] == ';') {
        tok_arr.array[tok_arr.length].type = TOK_LINE_TERMINATOR;
        return;
    }

    if (strlen(buffer) == 1 && !ISALPHA(buffer[0])) {
        tok_arr.array[tok_arr.length].type = TOK_SPECIAL_SYMBOLS;
        return;
    }

    tok_arr.array[tok_arr.length].type = TOK_IDENTIFIER;
    // printf("%d\n", tok_arr.array[tok_arr.length].type);
    return;
}
