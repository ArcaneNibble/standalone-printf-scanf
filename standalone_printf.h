#ifndef STANDALONE_PRINTF_H_
#define STANDALONE_PRINTF_H_

#include <stdarg.h>
#include <stdio.h>

int standalone_vcbprintf(void *restrict cb_state,
    void (*out_cb)(void *state, const char *s , size_t l),
    const char *restrict fmt, va_list ap);
int standalone_cbprintf(void *restrict cb_state,
    void (*out_cb)(void *state, const char *s , size_t l),
    const char *restrict fmt, ...);

int standalone_fprintf(FILE *restrict f, const char *restrict fmt, ...);
int standalone_snprintf(char *restrict s, size_t n, const char *restrict fmt, ...);

#endif
