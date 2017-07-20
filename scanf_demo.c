#include <stdio.h>
#include <string.h>
#include <wchar.h>
#include "standalone_scanf.h"

const char *mystr = "0.3932922657273";
size_t idx;

int my_getc(void *state) {
    printf("getc at %d", (int)idx);
    if (idx < strlen(mystr)) {
        printf(" -> '%c'\n", mystr[idx]);
        return (unsigned char)mystr[idx++];
    } else if (idx == strlen(mystr)) {
        printf(" -> EOF\n");
        idx++;
        return EOF;
    } else {
        printf(" -> OVERRUN!\n");
        idx++;
        return EOF;
    }
}

void my_ungetc(void *state, int c) {
    printf("unget '%c' %d\n", c, c);
}

int main (int argc, char **argv) {
    // float f;
    double d;
    // char s1[10];
    // char s2[10];
    // int i1, i2, i3;
    // wchar_t wc[2] = {0, 0};

    int ret = standalone_cbscanf(0, my_getc, my_ungetc, "%lf", &d);

    printf("ret = %d\n", ret);
    printf("The float is: %f %a\n", d, d);
    // printf("The string is: %s\n", s1);
    // printf("The string is: %s\n", s2);
    // printf("The integer is: %d\n", i1);
    // printf("The integer is: %d\n", i2);
    // printf("The integer is: %d\n", i3);
    // printf("The wide is: %08X %08X\n", wc[0], wc[1]);


    ret = sscanf(mystr, "%lf", &d);

    printf("reference ret = %d\n", ret);
    printf("reference The float is: %f %a\n", d, d);
    // printf("reference The string is: %s\n", s1);
    // printf("reference The string is: %s\n", s2);
    // printf("reference The integer is: %d\n", i1);
    // printf("reference The integer is: %d\n", i2);
    // printf("reference The integer is: %d\n", i3);
    // printf("reference The wide is: %08X %08X\n", wc[0], wc[1]);

    return 0;
}
