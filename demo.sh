x86_64-w64-mingw32-gcc-win32 -std=c99 -ggdb -O0 -Wall -pedantic -Wno-parentheses -c standalone_printf.c
x86_64-w64-mingw32-gcc-win32 -std=c99 -ggdb -O0 -Wall -pedantic -Wno-parentheses -c wtfnicode.c
x86_64-w64-mingw32-gcc-win32 -std=c99 -ggdb -O0 -Wall -pedantic -o printf_demo.exe printf_demo.c standalone_printf.o wtfnicode.o

gcc -std=c99 -ggdb -O0 -Wall -pedantic -Wno-parentheses -c standalone_printf.c
gcc -std=c99 -ggdb -O0 -Wall -pedantic -Wno-parentheses -c wtfnicode.c
gcc -std=c99 -ggdb -O0 -Wall -pedantic -o printf_demo printf_demo.c standalone_printf.o wtfnicode.o


x86_64-w64-mingw32-gcc-win32 -std=c99 -ggdb -O0 -Wall -pedantic -Wno-parentheses -c standalone_scanf.c
x86_64-w64-mingw32-gcc-win32 -std=c99 -ggdb -O0 -Wall -pedantic -Wno-parentheses -c wtfnicode.c
x86_64-w64-mingw32-gcc-win32 -std=c99 -ggdb -O0 -Wall -pedantic -o scanf_demo.exe scanf_demo.c standalone_scanf.o wtfnicode.o -lm

gcc -std=c99 -ggdb -O0 -Wall -pedantic -Wno-parentheses -c standalone_scanf.c
gcc -std=c99 -ggdb -O0 -Wall -pedantic -Wno-parentheses -c wtfnicode.c
gcc -std=c99 -ggdb -O0 -Wall -pedantic -o scanf_demo scanf_demo.c standalone_scanf.o wtfnicode.o -lm
