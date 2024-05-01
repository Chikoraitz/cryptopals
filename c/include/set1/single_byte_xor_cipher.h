#ifndef __XOR_DECRYPT__
#define __XOR_DECRYPT__

#include <stdio.h>
#include <stdlib.h>

#include "fixed_xor.h"
#include "utils.h"

/**
 * define LSB - Array index of the least significant byte.
 * @ARRAY_SIZE: Array size
 * 
 * In a raw binary byte array, the least significant byte is last element 
 * of the array. When dealing with single increments, it useful to 
 * determine the least significant byte index for detecting overflows 
*/
#define LSB(ARRAY_SIZE)  ARRAY_SIZE - 1

/**
 * define MSB - Array index of the most significant byte.
 * 
 * In a raw binary byte array, the most significant byte is first element 
 * of the array. When dealing with single increments, it useful to 
 * rename the 0 position to a more suggestive name to avoid magic numbers
 * throughout the codebase.
*/
#define MSB 0

/**
 * define ALPHABET_SIZE - Alphabet character array size.
 * 
 * In a raw binary array, the most significan byte is the first element
 * of the array.
*/
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
  Data text;
  byte * key;
} LanguageScore;


void xor_decrypt(LanguageScore *, const Data, const int);
int detect_single_byte_key_xor(FILE *, char *, char *);
double en_score(const char *, const int);

static byte generate_next_key_try(byte *, const int);
static void score_assessment(LanguageScore *, LanguageScore *, const int, const int);

/** @single_byte_xor_cipher.c */
extern const double freq_expected[];


#endif