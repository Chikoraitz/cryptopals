#ifndef __BASE64_HEADER__
#define __BASE64_HEADER__

#include <stdio.h>
#include <stdlib.h>

#include "utils.h"

/**
 * define BINARY_BLOCK_BUFFER_SIZE - Temporary buffer block size for allocating binary raw data
 * 
 * Base64 encoding operates over blocks of 3 bytes at each iteration.  
*/
#define BINARY_BLOCK_BUFFER_SIZE  3

/**
 * define BASE64_BLOCK_BUFFER_SIZE - Temporary buffer block size for allocating base64 characters
 * 
 * Base64 encoding converts each 3 blocks of binary raw data into blocks
 * of 4 bytes. This means that base64 encoding introduces an overhead of 33% in
 * the message itself.
*/
#define BASE64_BLOCK_BUFFER_SIZE  4

const int get_base64_size(const char *);

void base64_from_hex_string(char *, const char *);
void base64_from_raw(char *, const Data);

static int convert(char *, byte *, char *, int);
static void block_encode(char *, const byte *);

/** @base64.c */
extern const char base64_lookup_chars[];
extern const char base64_padding;

#endif