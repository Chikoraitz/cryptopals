#ifndef __BASE64_HEADER__
#define __BASE64_HEADER__

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#include "data_conversion.h"

#define BINARY_BLOCK_SIZE 3
#define BASE64_BLOCK_SIZE 4


const int get_base64_size_from_hexstr(const char *);
const int get_bytes_size_from_base64str(const char *);

void bytes_to_base64(const ByteStream, char *);
void base64_to_bytes(const char *, ByteStream *);

extern const char base64_lookup_chars[];
extern const char base64_padding;

#endif