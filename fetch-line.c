#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "h/fetch-line.h"


char *fetch_line(char * buf, int buflen, FILE *stream, int *lineno) {
    char *s;
    if (fgets(buf, buflen, stream) == NULL) {
        return NULL;
    }
    ++*lineno;
    if (buf[strlen(buf)] != '\n') {
        fprintf(stderr, "**** reading error");
        exit(EXIT_FAILURE);
    }
    s = trim_line(buf);
    if (*s = trim_line(buf)) {
        return s;
    } else {
        return fetch_line(buf, buflen, stream, lineno);
    }
}
