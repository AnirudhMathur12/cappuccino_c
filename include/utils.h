#ifndef UTILS
#define UTILS

#include <memory.h>
#include <stdio.h>
#include <stdlib.h>

#define THROW_ERR(str, ...) printf("\033[0;31m" str "\033[0m", __VA_ARGS__)

#define ISALPHA(chr) ((65 <= chr && chr <= 90) || (97 <= chr && chr <= 122))
#define ISNUM(chr) (48 <= chr && chr <= 57)
#define ISWHITESPACE(chr) (chr == 9 || chr == 32 || chr == 10)

char *read_file(const char *path);

#endif
