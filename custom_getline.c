#include "monty.h"
#include <stddef.h>

ssize_t custom_getline(char **lineptr, size_t *n, FILE *stream) {
    size_t bufsize = 0;
    ssize_t read_chars = 0;
    int c;

    if (!lineptr || !n || !stream) {
        return -1;
    }

    *lineptr = NULL;
    *n = 0;

    while ((c = fgetc(stream)) != EOF) {
        if ((size_t)read_chars >= bufsize) {
            bufsize += 128;
            char *new_lineptr = realloc(*lineptr, bufsize);
            if (!new_lineptr) {
                return -1; // Memory allocation error
            }
            *lineptr = new_lineptr;
            *n = bufsize;
        }

        (*lineptr)[read_chars++] = (char)c;

        if (c == '\n') {
            break;
        }
    }

    if (read_chars == 0 && c == EOF) {
        return -1;
    }

    (*lineptr)[read_chars] = '\0';
    return read_chars;
}
