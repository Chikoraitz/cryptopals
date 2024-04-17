#include <stdlib.h>

#include "fixed_xor.h"
#include "utils.h"
#include "../../include/set1/single_byte_xor_cipher.h"


/**
 * The function receives a cipher and the XOR key length, and deciphers
 * the XOR-encrypted message.
 * It expects a string and an integer, and returns a SymEncryptMessage 
 * data type variable - defined in utils.h
*/
SymEncryptMessage xor_decrypt(const char * cipher, const int key_len) {
  SymEncryptMessage d = { .status = Error, .algorithm = "XOR" };
  PlaintextScore best = { .plaintext = "", .score = 0 };
  /*
  size_t cipher_size = strlen(cipher) / BYTE_NIBBLES;

  byte * raw_key_try = (byte *) malloc(sizeof(byte) * key_len);
  byte * raw_cipher = (byte *) malloc(sizeof(byte) * cipher_size);
  raw_bytes(raw_cipher, cipher);
  
  
  // Brute-force key
  for(int i=0; i < cipher_size; i++) {
    raw_key_try = xor()

    // Call score function to each iteration and compare to best
    key_try = score(xor_encrypt(cipher, key), en);

    // Evaluate each output and choose the one with the best score
    if(key_try.score > best.score) {
      best.score = key_try.score;
      best.plaintext = key_try.plaintext;
    }
  }
  
  
  free(raw_cipher);
  free(raw_key_try);
  */

  return d;
}


/**
 * 
*/
PlaintextScore score(const char * plaintext_msg, int lang) {
  switch(lang) {
    default: return en_score(plaintext_msg);
  }
}


/**
 * 
*/
PlaintextScore en_score(const char * plaintext_msg) {
  // Devise some method for scoring a piece of English plaintext:
  // - Character frequency is a good metric
}