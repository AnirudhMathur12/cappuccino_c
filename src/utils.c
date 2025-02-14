#ifndef UTILS
#define UTILS
#include <memory.h>
#include <stdio.h>
#include <stdlib.h>

#define ISALPHA(chr) ((65 <= chr && chr <= 90) || (97 <= chr && chr <= 122))
#define ISNUM(chr) (48 <= chr && chr <= 57)
#define ISWHITESPACE(chr) (chr == 9 || chr == 32 || chr == 10)
#define ISBRACKET(chr)                                                                             \
    (chr == 40 || chr == 41 || chr == 123 || chr == 125 || chr == 91 || chr == 93)

char *read_file(const char *path) {
    FILE *fp = fopen(path, "r");
    if (fp == NULL) {
        printf("Could not open %s\n", path);
        return NULL;
    }

    fseek(fp, 0, SEEK_END);
    size_t size = ftell(fp);
    rewind(fp);

    char *buffer = (char *)malloc(size + 1);
    if (buffer == NULL) {
        printf("Buffer allocation to read file: %s failed.", path);
        return NULL;
    }
    fread(buffer, 1, size, fp);
    buffer[size] = '\0';

    fclose(fp);
    return buffer;
}
#endif
