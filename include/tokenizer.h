#ifndef TOKENIZER
#define TOKENIZER
#include "data_types.h"
#include "utils.h"
#include <stdlib.h>
#include <string.h>

void buffer_to_token(char *buffer);
TokenArray tokenize(char *data, char *file_name);

#endif
