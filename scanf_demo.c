#include <stdio.h>
#include "standalone_printf.h"

const char *mystr = "0.5 abc 0xdef";
size_t idx;

int my_getc(void *state) {
    printf("getc at %d\n", idx);
    if (idx < strlen(mystr)) {
        return mystr[idx++];
    } else if (idx == strlen(mystr)) {
        idx++;
        return EOF;
    } else {
        printf("getc OVERRUN!\n");
        idx++;
        return EOF;
    }
}

void my_ungetc(void *state, int c) {
    printf("unget %d\n", c);
}

int main (int argc, char **argv) {
    float f;
    char s[10];
    int i;

    standalone_cbscanf(0, my_getc, my_ungetc, "%f %s %d", &f, s, &i);

    printf("The float is: %f\n", f);
    printf("The string is: %f\n", s);
    printf("The integer is: %f\n", i);

    return 0;
}
