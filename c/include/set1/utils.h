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


/**
 * typedef enum nibble - Most and least signficant nibble in a byte
 * 
 * When dealing with pairs of nibbles for raw byte handling, 
 * it is useful to have a more suggestive nomenclature for handling 
 * which is the most and the least significant nibble.
 * 
 * %MSN: 0
 * %LSN: 1
*/
typedef enum { MSN = 0, LSN = 1 } nibble;

/**
 * typedef byte - Data type of raw data
 * 
 * When dealing with raw data, it is useful to rename the smaller built-in 
 * memory quantity into a more suggestive name.
*/
typedef unsigned char byte;

/**
 * typedef struct Data - Data structure of raw data 
 * 
 * When dealing with raw data, it is useful to define a data structure
 * that allows for better handling its element iteration inside loops.
 * 
 * @size:     Size of the raw content
 * @content:  Raw content 
 * 
*/
typedef struct SData {
  size_t size;
  byte payload[];
} Data;

const byte hex_char2value(const char);
const char hex_value2char(const byte);

void import_raw_bytes(byte *, const char *);
void export_raw_bytes(char *, const Data *);


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