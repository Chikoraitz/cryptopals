#ifndef __SINGLE_XOR_DECRYPT__
#define __SINGLE_XOR_DECRYPT__

#include <stdio.h>
#include <stdlib.h>

#include "../utils/data_conversion.h"

#define LSB(ARRAY_SIZE)  ARRAY_SIZE - 1
#define MSB 0
#define ALPHABET_SIZE 26 

/**
 * typedef struct LanguageScore - Data structure to represent English plaintext scores.
 * 
 * When dealing with plaintext scoring, it is useful to aggregate the required
 * data into a data structure that facillitates message data manipulation.
 * 
 * @score:    Score of a plaintext message
 * @text:     Plaintext data 
 * @key:      Key used to obtain this plaintext message 
*/
typedef struct SPlaintextScore {
  double score;
  ByteStream * decrypted;
  ByteStream * key;
} LanguageScore;

#define LANGUAGE_SCORE(msg_buf, msg_buf_size, key_buf, key_buf_size) { .score = 300, .decrypted = &(ByteStream) BYTESTREAM(msg_buf, msg_buf_size), .key = &(ByteStream) BYTESTREAM(key_buf, key_buf_size) }

double en_score(const char *, const int, const float);

/** @single_byte_xor_cipher.c */
extern const double freq_expected[];


#endif