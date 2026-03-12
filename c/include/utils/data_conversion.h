#ifndef __UTILS__
#define __UTILS__

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

/**
 * define NIBBLES_BYTE - Number of nibbles in a byte
 * 
 * Hexadecimal characters represent a nibble, so each pair of nibbles 
 * represent a byte.   
*/
#define NIBBLE_BYTE   2

/**
 * define BIT_NIBBLES - Number of bits in a nibble
 * 
 * Hexadecimal characters represent values between the range of 0 and 15 -
 * we need 4 bits to represent all values in this range.
*/
#define BIT_NIBBLE    4

/**
 * define BITS_IN__BYTE - Number of bits in a byte
 * 
 * A byte is composed by 8 bits.
*/
#define BITS_IN__BYTE      8

// Most/Least Significant Nibble
enum { MSN = 0, LSN = 1 };

typedef unsigned char byte;
typedef struct SByteStream {
  size_t size;
  byte * content;
} ByteStream;


void hexstr_to_bytes(const char *, ByteStream *);
void bytes_to_hexstr(const ByteStream, char *);

#endif