#ifndef STANDALONE_SCANF_H_
#define STANDALONE_SCANF_H_

#include <stdarg.h>

int standalone_vcbscanf(void *restrict cb_state,
    int (*getc_cb)(void *state),
    void (*ungetc_cb)(void *state, int c),
    const char *restrict fmt, va_list ap);
int standalone_cbscanf(void *restrict cb_state,
    int (*getc_cb)(void *state),
    void (*ungetc_cb)(void *state, int c),
    const char *restrict fmt, ...);

#endif
