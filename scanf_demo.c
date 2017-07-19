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
    char s1[10];
    char s2[10];
    int i1, i2, i3;

    int ret = standalone_cbscanf(0, my_getc, my_ungetc, "%f %s %n %i %s %n", &f, s1, &i1, &i2, s2, &i3);

    printf("ret = %d\n", ret);
    printf("The float is: %f\n", f);
    printf("The string is: %s\n", s1);
    printf("The string is: %s\n", s2);
    printf("The integer is: %d\n", i1);
    printf("The integer is: %d\n", i2);
    printf("The integer is: %d\n", i3);


    ret = sscanf(mystr, "%f %s %n %i %s %n", &f, s1, &i1, &i2, s2, &i3);

    printf("reference ret = %d\n", ret);
    printf("reference The float is: %f\n", f);
    printf("reference The string is: %s\n", s1);
    printf("reference The string is: %s\n", s2);
    printf("reference The integer is: %d\n", i1);
    printf("reference The integer is: %d\n", i2);
    printf("reference The integer is: %d\n", i3);

    return 0;
}
