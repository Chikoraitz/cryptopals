#ifndef __BASE64_HEADER__
#define __BASE64_HEADER__

#include <stdint.h>
#include <string.h>

#include "utils.h"


#define BLOCK_SIZE  3
#define BLOCK_STRING_SIZE BLOCK_SIZE + 1  // Null character


struct SEncodingIteration {
  byte buffer[BLOCK_STRING_SIZE];
  byte interpolated_data[BLOCK_STRING_SIZE + 1];
};

byte * hex2base64(char []);
byte convertHexChars2Byte(char, char);
byte char2hex(char);
byte * blockInterpolation(byte []);
byte * base64LookupBlockEncoding(byte []);

#endif

#ifndef __BASE64_LOOKUPCHARS__
#define __BASE64_LOOKUPCHARS__

static const char base64_lookup_chars[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
static const char base64_padding = '=';

#endif