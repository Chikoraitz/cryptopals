#ifndef __XOR_DECRYPT__
#define __XOR_DECRYPT__

#include "utils.h"

#define MAX_VALUE(SIZEOF) (2 ^ (8 * SIZEOF) - 1)

// Suported languages for plaintext scoring
typedef enum { en } lang;

typedef struct SPlaintextScore {
  char * plaintext;
  int score;
} PlaintextScore;

SymEncryptMessage xor_decrypt(const char *, const int);
PlaintextScore score(const char *, const int);
PlaintextScore en_score(const char *);

#endif