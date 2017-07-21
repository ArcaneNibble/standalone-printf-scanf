#include <errno.h>
#include <stddef.h>
#include <stdint.h>

#include "wtfnicode.h"

// Convert a Unicode code unit to UTF-8, but allow converting low/high
// surrogates blindly, producing WTF-8/CESU-8
size_t standalone_c32rtomb(char *restrict s, char32_t wc)
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

size_t standalone_c16rtomb(char *restrict s, char16_t c16, char16_t *restrict ps) {
    if (*ps) {
        // There was a high surrogate remembered in the state
        if (c16 - 0xdc00u >= 0x400) {
            // This current character is not a low surrogate (unpaired)
            int ret = standalone_c32rtomb(s, *ps);
            *ps = 0;
            return ret + standalone_c32rtomb(s + ret, c16);
        } else {
            // There is a properly paired high+low surrogate
            char32_t wc = (*ps - 0xd7c0 << 10) + (c16 - 0xdc00);
            *ps = 0;
            return standalone_c32rtomb(s, wc);
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
            return standalone_c32rtomb(s, c16);
        }
    }
}

size_t standalone_wcrtomb(char *restrict s, wchar_t wc, char16_t *restrict ps) {
#if WCHAR_MAX == 65535
    return standalone_c16rtomb(s, wc, ps);
#else
    return standalone_c32rtomb(s, wc);
#endif
}

/* Interval [a,b). Either a must be 80 or b must be c0, lower 3 bits clear. */
#define R(a,b) ((uint32_t)((a==0x80 ? 0x40u-b : 0u-a) << 23))

#define C(x) ( x<2 ? -1 : ( R(0x80,0xc0) | x ) )
#define D(x) C((x+16))
#define E(x) ( ( x==0 ? R(0xa0,0xc0) : \
                 R(0x80,0xc0) ) \
             | ( R(0x80,0xc0) >> 6 ) \
             | x )
#define F(x) ( ( x>=5 ? 0 : \
                 x==0 ? R(0x90,0xc0) : \
                 x==4 ? R(0x80,0xa0) : \
                 R(0x80,0xc0) ) \
             | ( R(0x80,0xc0) >> 6 ) \
             | ( R(0x80,0xc0) >> 12 ) \
             | x )

static const uint32_t bittab[] = {
                  C(0x2),C(0x3),C(0x4),C(0x5),C(0x6),C(0x7),
    C(0x8),C(0x9),C(0xa),C(0xb),C(0xc),C(0xd),C(0xe),C(0xf),
    D(0x0),D(0x1),D(0x2),D(0x3),D(0x4),D(0x5),D(0x6),D(0x7),
    D(0x8),D(0x9),D(0xa),D(0xb),D(0xc),D(0xd),D(0xe),D(0xf),
    E(0x0),E(0x1),E(0x2),E(0x3),E(0x4),E(0x5),E(0x6),E(0x7),
    E(0x8),E(0x9),E(0xa),E(0xb),E(0xc),E(0xd),E(0xe),E(0xf),
    F(0x0),F(0x1),F(0x2),F(0x3),F(0x4)
};

/* Upper 6 state bits are a negative integer offset to bound-check next byte */
/*    equivalent to: ( (b-0x80) | (b+offset) ) & ~0x3f      */
#define OOB(c,b) (((((b)>>3)-0x10)|(((b)>>3)+((int32_t)(c)>>26))) & ~7)

#define SA 0xc2u
#define SB 0xf4u

size_t standalone_mbrtowc(char32_t *restrict wc, const char *restrict src, size_t n, unsigned *restrict st)
{
    unsigned c;
    const unsigned char *s = (const void *)src;
    const unsigned N = n;
    char32_t dummy;

    c = *(unsigned *)st;
    
    if (!s) {
        if (c) goto ilseq;
        return 0;
    } else if (!wc) wc = &dummy;

    if (!n) return -2;
    if (!c) {
        if (*s < 0x80) return !!(*wc = *s);
        if (*s-SA > SB-SA) goto ilseq;
        c = bittab[*s++-SA]; n--;
    }

    if (n) {
        if (OOB(c,*s)) goto ilseq;
loop:
        c = c<<6 | *s++-0x80; n--;
        if (!(c&(1U<<31))) {
            *(unsigned *)st = 0;
            *wc = c;
            return N-n;
        }
        if (n) {
            if (*s-0x80u >= 0x40) goto ilseq;
            goto loop;
        }
    }

    *(unsigned *)st = c;
    return -2;
ilseq:
    *(unsigned *)st = 0;
    errno = EILSEQ;
    return -1;
}
