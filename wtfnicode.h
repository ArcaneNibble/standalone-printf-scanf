#ifndef WTFNICODE_H_
#define WTFNICODE_H_

#include <uchar.h>

// Convert a Unicode code unit to UTF-8, but allow converting low/high
// surrogates blindly, producing WTF-8/CESU-8
size_t standalone_c32rtomb(char *restrict s, char32_t wc);

// Converts UTF-16 to WTF-8. Does not have exactly the same semantics as the "real" c16rtomb!
size_t standalone_c16rtomb(char *restrict s, char16_t c16, char16_t *restrict ps);

// Converts wide characters to WTF-8. Does not have exactly the same semantics as the "real" wcrtomb!
size_t standalone_wcrtomb(char *restrict s, wchar_t wc, char16_t *restrict ps);

#endif
