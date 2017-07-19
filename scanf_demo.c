#include <stdio.h>
#include <string.h>
#include "standalone_scanf.h"

const char *mystr = "0.1234 abc 0xdef ghi";
size_t idx;

int my_getc(void *state) {
    printf("getc at %d", (int)idx);
    if (idx < strlen(mystr)) {
        printf(" -> '%c'\n", mystr[idx]);
        return mystr[idx++];
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
    float f;
    char s[10];
    int i;

    int ret = standalone_cbscanf(0, my_getc, my_ungetc, "%5f %s %n", &f, s, &i);

    printf("ret = %d\n", ret);
    printf("The float is: %f\n", f);
    printf("The string is: %s\n", s);
    printf("The integer is: %d\n", i);


    ret = sscanf(mystr, "%5f %s %n", &f, s, &i);

    printf("reference ret = %d\n", ret);
    printf("reference The float is: %f\n", f);
    printf("reference The string is: %s\n", s);
    printf("reference The integer is: %d\n", i);

    return 0;
}
