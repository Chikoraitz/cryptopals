#ifndef __AES_HEADER__
#define __AES_HEADER__

#include <stdlib.h>
#include <stdint.h>

#include "../../include/utils/data_conversion.h"
#include "../../include/utils/debug.h"
#include "../../include/crypto/xor.h"

#define AES_BLOCK_SIZE        16
#define AES_STATE_ROW_SIZE    4
#define AES_STATE_COLUMN_SIZE 4

typedef enum { 
  FORWARD = 0,
  INVERSE = 1 
} aes_dir_t;

typedef enum { 
  ECB = 0 
} aes_mode_t;

typedef struct {
  size_t      key_len;
  aes_mode_t  mode;
  uint8_t     rounds;
  byte *      key;
  byte        iv[16];
} aes_ctx_t;

typedef enum {
  AES_OK =         0,
  AES_EINVAL =    -1,
  AES_EKEYLEN =   -2
} aes_status_code_t;

#define AES128_DEFAULT  (aes_ctx_t){ .key_len = 16, .rounds = 10 }
#define AES192_DEFAULT  (aes_ctx_t){ .key_len = 24, .rounds = 12 }
#define AES256_DEFAULT  (aes_ctx_t){ .key_len = 32, .rounds = 14 }
#define AES_WORD_SIZE   4
#define AES_MAX_ROUNDS  15

// Public AES APIs
aes_status_code_t aes_encrypt(const aes_ctx_t);
aes_status_code_t aes_decrypt(const aes_ctx_t, const ByteStream, ByteStream *);

aes_status_code_t load_state(const byte[AES_BLOCK_SIZE], byte[AES_STATE_COLUMN_SIZE][AES_STATE_ROW_SIZE]);
aes_status_code_t store_state(const byte[AES_STATE_COLUMN_SIZE][AES_STATE_ROW_SIZE], byte[AES_BLOCK_SIZE]);

const char * aes_strerror(aes_status_code_t code);
void debug_aes_state(const char*, byte[AES_STATE_COLUMN_SIZE][AES_STATE_ROW_SIZE]);


// PKCS#7 Padding
aes_status_code_t pkcs7_pad(const ByteStream, ByteStream*);

// Encryption/Decryption Modes
aes_status_code_t ecb_encrypt(const aes_ctx_t, const ByteStream, ByteStream *);
aes_status_code_t ecb_decrypt(const aes_ctx_t, const ByteStream, ByteStream *);


// AES algorithm
extern const byte FORWARD_SBOX[256];
extern const byte INVERSE_SBOX[256];
extern const byte PRESET_MATRIX[2][AES_STATE_COLUMN_SIZE][AES_STATE_ROW_SIZE];
extern const byte ROUND_CONSTANTS[11];

static inline byte add_gf8(byte b1, byte b2) { return b1 ^ b2; }
static inline byte mult_gf8(byte, byte);
static inline void mix_columm_matrix_multiply(aes_dir_t, byte*[AES_STATE_COLUMN_SIZE]);
static inline void g(byte[AES_WORD_SIZE], const uint8_t); // Transformation Chain: RotWord + SubWord + Rcon

void aes_cipher_block(const aes_ctx_t, const byte[AES_BLOCK_SIZE], byte[AES_BLOCK_SIZE]);
void aes_inverse_cipher_block(const aes_ctx_t, const byte[AES_BLOCK_SIZE], byte[AES_BLOCK_SIZE]);

void aes_sub_bytes(aes_dir_t, byte[AES_STATE_COLUMN_SIZE][AES_STATE_ROW_SIZE]);
void aes_shift_rows(aes_dir_t, byte[AES_STATE_COLUMN_SIZE][AES_STATE_ROW_SIZE]);
void aes_mix_columns(aes_dir_t, byte[AES_STATE_COLUMN_SIZE][AES_STATE_ROW_SIZE]);
void aes_add_round_key(byte[AES_STATE_COLUMN_SIZE][AES_STATE_ROW_SIZE], byte[AES_STATE_COLUMN_SIZE][AES_STATE_ROW_SIZE]);
void aes_key_expansion(const uint16_t, byte[AES_STATE_COLUMN_SIZE][AES_STATE_ROW_SIZE], const uint8_t);


#endif