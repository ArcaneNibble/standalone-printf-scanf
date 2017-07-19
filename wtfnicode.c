#include <errno.h>
#include <stddef.h>

#include "wtfnicode.h"

// Convert a Unicode code unit to UTF-8, but allow converting low/high
// surrogates blindly, producing WTF-8/CESU-8
static size_t my_wcrtomb(char *restrict s, char32_t wc)
{
	if (!s) return 1;
	if (wc < 0x80) {
		*s = wc;
		return 1;
	} else if (wc < 0x800) {
		*s++ = 0xc0 | (wc>>6);
		*s = 0x80 | (wc&0x3f);
		return 2;
	} else if (wc < 0x10000) {
		*s++ = 0xe0 | (wc>>12);
		*s++ = 0x80 | ((wc>>6)&0x3f);
		*s = 0x80 | (wc&0x3f);
		return 3;
	} else if (wc-0x10000 < 0x100000) {
		*s++ = 0xf0 | (wc>>18);
		*s++ = 0x80 | ((wc>>12)&0x3f);
		*s++ = 0x80 | ((wc>>6)&0x3f);
		*s = 0x80 | (wc&0x3f);
		return 4;
	}
	errno = EILSEQ;
	return -1;
}

// Converts UTF-16 to WTF-8. Does not have exactly the same semantics as the "real" c16rtomb!
size_t standalone_c16rtomb(char *restrict s, char16_t c16, char16_t *restrict ps) {
    if (*ps) {
        // There was a high surrogate remembered in the state
        if (c16 - 0xdc00u >= 0x400) {
            // This current character is not a low surrogate (unpaired)
            int ret = my_wcrtomb(s, *ps);
            *ps = 0;
            return ret + my_wcrtomb(s + ret, c16);
        } else {
            // There is a properly paired high+low surrogate
            char32_t wc = (*ps - 0xd7c0 << 10) + (c16 - 0xdc00);
            *ps = 0;
            return my_wcrtomb(s, wc);
        }
    } else {
        // There was no high surrogate remembered in the state
        if (c16 - 0xd800u < 0x400) {
            // This is a high surrogate
            *ps = c16;
            return 0;
        } else {
            // This is not a high surrogate - either a normal character or
            // something unpaired
            return my_wcrtomb(s, c16);
        }
    }
}

// Converts wide characters to WTF-8. Does not have exactly the same semantics as the "real" wcrtomb!
size_t standalone_wcrtomb(char *restrict s, wchar_t wc, char16_t *restrict ps) {
#if WCHAR_MAX == 65535
    return standalone_c16rtomb(s, wc, ps);
#else
    return my_wcrtomb(s, wc);
#endif
}
