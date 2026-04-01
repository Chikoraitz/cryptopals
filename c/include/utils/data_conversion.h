#ifndef __UTILS__
#define __UTILS__

#include <string.h>
#include <stdio.h>
#include <stdlib.h>


#define NIBBLE_BYTE   2
#define BIT_NIBBLE 4
#define BITS_IN__BYTE 8

enum { MSN = 0, LSN = 1 };

typedef enum {
  FALSE = 0,
  TRUE = 1,
} boolean_t;

typedef unsigned char byte;
typedef struct SByteStream {
  size_t size;
  byte * content;
} ByteStream;

#define BYTESTREAM(buf, s) { .size = s, .content = buf }


void hexstr_to_bytes(const char *, ByteStream *);
void bytes_to_hexstr(const ByteStream, char *);

#endif