#ifndef __FIXED_XOR_HEADER__
#define __FIXED_XOR_HEADER__

#include <stdint.h>

#include "../utils/data_conversion.h"
#include "../analysis/en_score.h"

#define MAX(x, y) (((x) > (y)) ? (x) : (y))

void xor(const ByteStream, const ByteStream, ByteStream *);
void single_xor_decrypt(const ByteStream, LanguageScore *);
int guess_xor_keysize(const ByteStream, const int, const int);


#endif