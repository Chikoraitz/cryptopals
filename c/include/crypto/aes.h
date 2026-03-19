#ifndef __AES_HEADER__
#define __AES_HEADER__

#include <stdlib.h>
#include <stdint.h>

#include "../../include/utils/data_conversion.h"
#include "../../include/utils/debug.h"
#include "../../include/crypto/xor.h"

#define AES_BLOCK_SIZE 16
#define AES_STATE_ROW_SIZE 4
#define AES_STATE_COLUMN_SIZE 4

typedef enum { 
  FORWARD = 0,
  INVERSE = 1 
} aes_dir_t;

typedef enum { 
  ECB = 0 
} aes_mode_t;

typedef struct {
  size_t key_len;
  uint8_t rounds;
  byte iv[16];
} aes_ctx_t;

#define AES128_DEFAULT (aes_ctx_t){ .key_len = 16, .rounds = 10 }
#define AES192_DEFAULT (aes_ctx_t){ .key_len = 24, .rounds = 12 }
#define AES256_DEFAULT (aes_ctx_t){ .key_len = 32, .rounds = 14 }

void aes_encrypt(const aes_ctx_t, const aes_mode_t);
void aes_decrypt(const aes_ctx_t, const aes_mode_t, const ByteStream, ByteStream *);

// AES algorithm
extern const byte SBOX[256];
extern const byte INVERSE_SBOX[256];
extern const byte COLUMN_MATRIX[2][AES_BLOCK_SIZE];

static inline byte addition_gf8(byte b1, byte b2) { return b1 ^ b2; }
static inline byte multiplication_gf8(byte, byte);

void aes_key_expansion();
byte aes_sub_bytes(aes_dir_t, byte);
void aes_shift_rows(aes_dir_t, byte[AES_BLOCK_SIZE]);
void aes_mix_columns(aes_dir_t, byte[AES_BLOCK_SIZE]);
void aes_add_round_key();
void aes_inverse_cipher_block(const uint8_t, const byte[AES_BLOCK_SIZE], const byte[AES_BLOCK_SIZE], byte[AES_BLOCK_SIZE]);
void aes_cipher_block(const uint8_t, const byte[AES_BLOCK_SIZE], const byte[AES_BLOCK_SIZE], byte[AES_BLOCK_SIZE]);


// Encryption/Decryption Modes
void ecb_encrypt();
void ecb_decrypt(const aes_ctx_t, const ByteStream, const ByteStream, ByteStream *);

#endif