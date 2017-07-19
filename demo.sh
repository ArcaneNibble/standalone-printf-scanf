gcc -ggdb -O0 -Wall -Wno-parentheses -c standalone_printf.c
gcc -ggdb -O0 -Wall -o printf_demo printf_demo.c standalone_printf.o
