#ifndef STANDALONE_SCANF_H_
#define STANDALONE_SCANF_H_

#include <stdarg.h>
#include <stdio.h>
#include <inttypes.h>

int standalone_vcbscanf(void *restrict cb_state,
    int (*getc_cb)(void *state),
    void (*ungetc_cb)(void *state, int c),
    const char *restrict fmt, va_list ap);
int standalone_cbscanf(void *restrict cb_state,
    int (*getc_cb)(void *state),
    void (*ungetc_cb)(void *state, int c),
    const char *restrict fmt, ...);

int standalone_fscanf(FILE *restrict f, const char *restrict fmt, ...);
int standalone_sscanf(const char *restrict s, const char *restrict fmt, ...);


float standalone_strtof(const char *restrict s, char **restrict p);
double standalone_strtod(const char *restrict s, char **restrict p);
long double standalone_strtold(const char *restrict s, char **restrict p);

unsigned long long standalone_strtoull(const char *restrict s, char **restrict p, int base);
long long standalone_strtoll(const char *restrict s, char **restrict p, int base);
unsigned long standalone_strtoul(const char *restrict s, char **restrict p, int base);
long standalone_strtol(const char *restrict s, char **restrict p, int base);
intmax_t standalone_strtoimax(const char *restrict s, char **restrict p, int base);
uintmax_t standalone_strtoumax(const char *restrict s, char **restrict p, int base);

#endif
