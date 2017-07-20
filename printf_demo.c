#include <stdio.h>
#include "standalone_printf.h"
#include "wtfnicode.h"

int main (int argc, char **argv) {
    standalone_fprintf(stdout, "test %d %x %.100f %ls\n", 123, 456, 0.1, L"wide\xD801\xDC37str\x10437ing");

    char32_t wc;
    unsigned wcstate = 0;
    int ret = standalone_mbrtowc(&wc, "\xed\xa0\x81", 3, &wcstate);
    printf("wc is (%d) %08x\n", ret, wc);

    char small_buf[8];
    ret = standalone_snprintf(small_buf, sizeof(small_buf), "%.1f test", 0.123);
    printf("small buf is (%d) %s\n", ret, small_buf);

    return 0;
}
