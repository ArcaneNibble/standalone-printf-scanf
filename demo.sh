# gcc -ggdb -O0 -Wall -Wno-parentheses -c standalone_printf.c
# gcc -ggdb -O0 -Wall -Wno-parentheses -c wtfnicode.c
# gcc -ggdb -O0 -Wall -o printf_demo printf_demo.c standalone_printf.o wtfnicode.o

# x86_64-w64-mingw32-gcc-win32 -ggdb -O0 -Wall -Wno-parentheses -c standalone_printf.c
# x86_64-w64-mingw32-gcc-win32 -ggdb -O0 -Wall -Wno-parentheses -c wtfnicode.c
# x86_64-w64-mingw32-gcc-win32 -ggdb -O0 -Wall -o printf_demo.exe printf_demo.c standalone_printf.o wtfnicode.o

gcc -ggdb -O0 -Wall -Wno-parentheses -c standalone_scanf.c
gcc -ggdb -O0 -Wall -o scanf_demo scanf_demo.c standalone_scanf.o
