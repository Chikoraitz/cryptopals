#ifndef __FIXED_XOR_HEADER__
#define __FIXED_XOR_HEADER__

#include <stdint.h>

#include "../utils/data_conversion.h"
#include "../analysis/en_score.h"
#include "../analysis/hamming.h"


#define MAX(x, y) (((x) > (y)) ? (x) : (y))

void xor(const ByteStream, const ByteStream, ByteStream *);
void single_xor_decrypt(const ByteStream, LanguageScore *, const float);
int guess_xor_keysize(const ByteStream, const int, const int, const int);
void transpose_vigenere_cipher(const ByteStream, ByteStream *, const int, const int);

void single_xor_decrypt_debug(const ByteStream, byte, float);

#endif