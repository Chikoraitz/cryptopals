#ifndef __AES_HEADER__
#define __AES_HEADER__

#include <stdlib.h>
#include <stdint.h>

#include "../../include/utils/data_conversion.h"

enum mode { ECB = 0 };

typedef struct {
  size_t key_len;
  uint8_t rounds;
} AES_CONFIG;

#define AES128_DEFAULT (AES_CONFIG){ .key_len = 16, .rounds = 10 }
#define AES192_DEFAULT (AES_CONFIG){ .key_len = 24, .rounds = 12 }
#define AES256_DEFAULT (AES_CONFIG){ .key_len = 32, .rounds = 14 }

void aes_encrypt(AES_CONFIG, enum mode);
void aes_decrypt(AES_CONFIG, const ByteStream, ByteStream *, enum mode);

extern const char SBOX[0xff];

// Encryption/Decryption Modes
void ecb_encrypt();
void ecb_decrypt();

#endif