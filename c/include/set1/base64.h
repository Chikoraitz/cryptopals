#ifndef __BASE64_SET1_HEADER__
#define __BASE64_SET1_HEADER__

#include <stdio.h>
#include <stdlib.h>

#include "../utils/data_conversion.h"

#define BINARY_BLOCK_SIZE 3
#define BASE64_BLOCK_SIZE 4


const int get_base64_size(const char *);
void bytes_to_base64(const byte *, char *, const size_t);

extern const char base64_lookup_chars[];
extern const char base64_padding;

#endif