#include <stdio.h>
#include "standalone_printf.h"

void my_out(void *cb_state, const char *s, size_t l) {
    printf("Stuff was output (%ld): ", l);
    fwrite(s, 1, l, stdout);
    printf("\n");
}

int main (int argc, char **argv) {
    standalone_cbprintf(0, my_out, "test %d %x %f %ls\n", 123, 456, 0.5, L"wide\xD801\xDC37str\x10437ing");

    return 0;
}
