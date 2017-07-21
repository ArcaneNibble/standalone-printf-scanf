x86_64-w64-mingw32-gcc-win32 -std=c99 -ggdb -O0 -Wall -pedantic -Wno-parentheses -c standalone_printf.c
x86_64-w64-mingw32-gcc-win32 -std=c99 -ggdb -O0 -Wall -pedantic -Wno-parentheses -c wtfnicode.c
x86_64-w64-mingw32-gcc-win32 -std=c99 -ggdb -O0 -Wall -pedantic -o printf_demo.exe printf_demo.c standalone_printf.o wtfnicode.o

clang -std=c99 -ggdb -O0 -Wall -pedantic -Wno-parentheses -c standalone_printf.c
clang -std=c99 -ggdb -O0 -Wall -pedantic -Wno-parentheses -c wtfnicode.c
clang -std=c99 -ggdb -O0 -Wall -pedantic -o printf_demo printf_demo.c standalone_printf.o wtfnicode.o


x86_64-w64-mingw32-gcc-win32 -std=c99 -ggdb -O0 -Wall -pedantic -Wno-parentheses -c standalone_printf.c
x86_64-w64-mingw32-gcc-win32 -std=c99 -ggdb -O0 -Wall -pedantic -Wno-parentheses -c standalone_scanf.c
x86_64-w64-mingw32-gcc-win32 -std=c99 -ggdb -O0 -Wall -pedantic -Wno-parentheses -c wtfnicode.c
x86_64-w64-mingw32-gcc-win32 -std=c99 -ggdb -O0 -Wall -pedantic -o scanf_demo.exe scanf_demo.c standalone_scanf.o standalone_printf.o wtfnicode.o -lm

clang -std=c99 -ggdb -O0 -Wall -pedantic -Wno-parentheses -c standalone_printf.c
clang -std=c99 -ggdb -O0 -Wall -pedantic -Wno-parentheses -c standalone_scanf.c
clang -std=c99 -ggdb -O0 -Wall -pedantic -Wno-parentheses -c wtfnicode.c
clang -std=c99 -ggdb -O0 -Wall -pedantic -o scanf_demo scanf_demo.c standalone_scanf.o standalone_printf.o wtfnicode.o -lm
