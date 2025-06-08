#ifndef __BASE64_SET1_HEADER__
#define __BASE64_SET1_HEADER__

#include <stdio.h>
#include <stdlib.h>

#include "../utils/data_conversion.h"
#include "../utils/base64.h"

const int get_base64_size(const char *);

void base64_encode_hex_string(char *, const char *);
void base64_decode_to_hex_string(char *, const char *);

void base64_encode_raw(char *, const Data *);
void base64_decode_raw(Data *, const char *);


#endif