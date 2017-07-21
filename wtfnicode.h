/*
    This file contains standalone "work-alike" functions for various wide/narrow
    character conversions. These functions explicitly rejects using the global
    locale settings to decide what to do. Instead, they all work on
    "Unicode-like" data. These functions are derived from musl, but they have
    been modified to accept more bogus input (described below). Note that there
    are some _incompatible_ changes as well: the types of some arguments and
    return values have been modified, and functions that accept a state variable
    now _require_ it and will not use a static variable instead.
*/

#ifndef WTFNICODE_H_
#define WTFNICODE_H_

#include <wchar.h>
#include <uchar.h>

// Convert a 32-bit code unit to a series of 8-bit code units. This conversion
// will "naively" use a UTF-8-like transformation on the input value.
// Values above 0x10FFFF will be rejected, but values in the range
// [0xD800, 0xDFFF] are _explicitly accepted_. The net result is a valid
// Unicode code point given as a UTF-32 code unit will be converted to legal
// UTF-8 output. However, a UTF-16 surrogate extended to 32 bits and passed
// as the input will be converted to WTF-8/CESU-8 instead.
size_t standalone_c32rtomb(char *restrict s, char32_t wc);

// Converts UTF-16 input into WTF-8 output. This conversion is stateful.
size_t standalone_c16rtomb(char *restrict s, char16_t c16, char16_t *restrict ps);

// Calls either standalone_c32rtomb or standalone_c16rtomb, depending on the
// size of wchar_t.
size_t standalone_wcrtomb(char *restrict s, wchar_t wc, char16_t *restrict ps);

// Accepts as input the union of UTF-8 and CESU-8 and produces 32-bit code
// units as output. If the input is well-formed UTF-8, the output will be
// well-formed UTF-32. If the input is WTF-8, the output will contain a mix
// of well-formed UTF-32 and unpaired UTF-16 surrogates extended to 32 bits.
// If the input is CESU-8, the output will not be well-formed UTF-32 but will
// contain a mix of UTF-32 and potentially paired or unpaired UTF-16 surrogates
// (extended to 32 bits). This function _will not_ attempt to convert paired
// CESU-8 surrogates into a valid UTF-32 code unit. In other words, this
// function blindly applies the UTF-8 decode algorithm and does not check
// for surrogates being produced. However, it does check for over-long
// sequences and sequences that would produce values above 0x10FFFF.
size_t standalone_mbrtowc(char32_t *restrict wc, const char *restrict src, size_t n, unsigned *restrict st);

#endif
