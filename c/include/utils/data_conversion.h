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
 * define BIT_BYTE - Number of bits in a byte
 * 
 * A byte is composed by 8 bits.
*/
#define BIT_BYTE      8

// Most/Least Significant Nibble
enum { MSN = 0, LSN = 1 };

typedef unsigned char byte;
typedef struct SData {
  size_t size;
  byte payload[];
} Data;


void hexstr_to_bytes(const char *, byte *);
void bytes_to_hexstr(const byte *, char *, const size_t);


/**
 * 
*/
static inline Data * allocate_bytes(size_t size) {
  Data * d = calloc(sizeof(Data) + size, sizeof(byte));
  
  if(d == NULL) {
    printf("Unable to allocate memory...");
    exit(EXIT_FAILURE);
  }

  memcpy(d, &(Data const){.size = size}, sizeof(Data));

  return d;
}


/**
 * 
*/
static inline void deallocate(Data * data) {
  free(data);
}


#endif