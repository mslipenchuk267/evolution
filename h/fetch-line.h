#ifndef H_FETCH_LINE_H
#define H_FETCH_LINE_H
#include <bits/types/FILE.h>

static char *trim_line(char * s);
char *fetch_line(char * buf, int buflen, FILE *stream, int *lineno);
#endif //H_FETCH_LINE_H
