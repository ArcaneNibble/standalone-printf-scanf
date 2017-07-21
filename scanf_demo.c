#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>
#include "standalone_scanf.h"
#include "standalone_printf.h"

const char *mystr = "0x3932922657273";

int main (int argc, char **argv) {
    // float f;
    // double d;
    // char s1[10];
    // char s2[10];
    // int i1, i2, i3;
    // wchar_t wc[2] = {0, 0};

    // int ret = standalone_fscanf(stdin, "%lf", &d);

    // printf("ret = %d\n", ret);
    // printf("The float is: %f %a\n", d, d);
    // printf("The string is: %s\n", s1);
    // printf("The string is: %s\n", s2);
    // printf("The integer is: %d\n", i1);
    // printf("The integer is: %d\n", i2);
    // printf("The integer is: %d\n", i3);
    // printf("The wide is: %08X %08X\n", wc[0], wc[1]);


    // ret = fscanf(stdin, "%lf", &d);

    // printf("reference ret = %d\n", ret);
    // printf("reference The float is: %f %a\n", d, d);
    // printf("reference The string is: %s\n", s1);
    // printf("reference The string is: %s\n", s2);
    // printf("reference The integer is: %d\n", i1);
    // printf("reference The integer is: %d\n", i2);
    // printf("reference The integer is: %d\n", i3);
    // printf("reference The wide is: %08X %08X\n", wc[0], wc[1]);

    char *strend;
    standalone_fprintf(stdout, "The number is: %jd\n", standalone_strtoimax(mystr, &strend, 0));
    standalone_fprintf(stdout, "Used %td chars\n", strend - mystr);

    standalone_fprintf(stdout, "reference The number is: %jd\n", strtoimax(mystr, &strend, 0));
    standalone_fprintf(stdout, "reference Used %td chars\n", strend - mystr);

    return 0;
}
