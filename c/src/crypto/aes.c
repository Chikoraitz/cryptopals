#include "../../include/crypto/aes.h"


// === Public AES APIs

aes_status_code_t load_state(const byte in[AES_BLOCK_SIZE], byte out[AES_STATE_COLUMN_SIZE][AES_STATE_ROW_SIZE]) {
  for(int b = 0; b < AES_BLOCK_SIZE; b++) {
    out[b % AES_STATE_ROW_SIZE][b / AES_STATE_COLUMN_SIZE] = in[b];
  }

  return AES_OK;
}


aes_status_code_t store_state(const byte in[AES_STATE_COLUMN_SIZE][AES_STATE_ROW_SIZE], byte out[AES_BLOCK_SIZE]) {
  for(int b = 0; b < AES_BLOCK_SIZE; b++) {
    out[b] = in[b % AES_STATE_ROW_SIZE][b / AES_STATE_COLUMN_SIZE];
  }

  return AES_OK;
}


const char * aes_strerror(aes_status_code_t code) {
  const static char * status_msg[3] = {
    "success", "invalid argument", "unsupported key length"
  };

  return status_msg[-code];
}


aes_status_code_t aes_encrypt(aes_ctx_t config) {
  // WIP
}


aes_status_code_t aes_decrypt(const aes_ctx_t ctx, const ByteStream ciphertext, ByteStream * plaintext) {
  aes_status_code_t (* aes_decrypt_mode_fn)(const aes_ctx_t, const ByteStream, ByteStream *);

  switch(ctx.mode) {
    case ECB: aes_decrypt_mode_fn = &ecb_decrypt; break;
  }

  return aes_decrypt_mode_fn(ctx, ciphertext, plaintext);
}



void debug_aes_state(const char * prefix, byte state[AES_STATE_COLUMN_SIZE][AES_STATE_ROW_SIZE]) {
  printf("\n%s", prefix);
  for(int col=0; col < AES_STATE_COLUMN_SIZE; col++) {
    printf("\n\t");
    for(int row=0; row < AES_STATE_ROW_SIZE; row++) {
      printf("0x%2x ", state[col][row]);
    }
  }
  printf("\n");
}


// === AES modes of operations

aes_status_code_t pkcs7_pad(const ByteStream in, ByteStream * out) {
  return AES_OK;
}


aes_status_code_t ecb_encrypt(const aes_ctx_t, const ByteStream plaintext, ByteStream * cipher) {
  // WIP
  return AES_OK;
}


aes_status_code_t ecb_decrypt(const aes_ctx_t ctx, const ByteStream cipher, ByteStream * plaintext) {
  byte cipher_block[AES_BLOCK_SIZE];

  // Error handling
  if(cipher.size != plaintext->size) return AES_EINVAL;
  
  if((cipher.size % AES_BLOCK_SIZE) != 0) {
    // Perform padding
    return AES_EKEYLEN;
  }

  for(int offset=0; offset < cipher.size; offset += AES_BLOCK_SIZE) {
    memcpy(cipher_block, cipher.content + offset, AES_BLOCK_SIZE);
    aes_inverse_cipher_block(ctx, cipher.content + offset, plaintext->content + offset);
  }

  plaintext->content[plaintext->size] = 0;

  return AES_OK;
}


// === AES Algorithm

const byte FORWARD_SBOX[256] = {
  //0     1    2      3     4    5     6     7      8    9     A      B    C     D     E     F
  0x63, 0x7c, 0x77, 0x7b, 0xf2, 0x6b, 0x6f, 0xc5, 0x30, 0x01, 0x67, 0x2b, 0xfe, 0xd7, 0xab, 0x76,
  0xca, 0x82, 0xc9, 0x7d, 0xfa, 0x59, 0x47, 0xf0, 0xad, 0xd4, 0xa2, 0xaf, 0x9c, 0xa4, 0x72, 0xc0,
  0xb7, 0xfd, 0x93, 0x26, 0x36, 0x3f, 0xf7, 0xcc, 0x34, 0xa5, 0xe5, 0xf1, 0x71, 0xd8, 0x31, 0x15,
  0x04, 0xc7, 0x23, 0xc3, 0x18, 0x96, 0x05, 0x9a, 0x07, 0x12, 0x80, 0xe2, 0xeb, 0x27, 0xb2, 0x75,
  0x09, 0x83, 0x2c, 0x1a, 0x1b, 0x6e, 0x5a, 0xa0, 0x52, 0x3b, 0xd6, 0xb3, 0x29, 0xe3, 0x2f, 0x84,
  0x53, 0xd1, 0x00, 0xed, 0x20, 0xfc, 0xb1, 0x5b, 0x6a, 0xcb, 0xbe, 0x39, 0x4a, 0x4c, 0x58, 0xcf,
  0xd0, 0xef, 0xaa, 0xfb, 0x43, 0x4d, 0x33, 0x85, 0x45, 0xf9, 0x02, 0x7f, 0x50, 0x3c, 0x9f, 0xa8,
  0x51, 0xa3, 0x40, 0x8f, 0x92, 0x9d, 0x38, 0xf5, 0xbc, 0xb6, 0xda, 0x21, 0x10, 0xff, 0xf3, 0xd2,
  0xcd, 0x0c, 0x13, 0xec, 0x5f, 0x97, 0x44, 0x17, 0xc4, 0xa7, 0x7e, 0x3d, 0x64, 0x5d, 0x19, 0x73,
  0x60, 0x81, 0x4f, 0xdc, 0x22, 0x2a, 0x90, 0x88, 0x46, 0xee, 0xb8, 0x14, 0xde, 0x5e, 0x0b, 0xdb,
  0xe0, 0x32, 0x3a, 0x0a, 0x49, 0x06, 0x24, 0x5c, 0xc2, 0xd3, 0xac, 0x62, 0x91, 0x95, 0xe4, 0x79,
  0xe7, 0xc8, 0x37, 0x6d, 0x8d, 0xd5, 0x4e, 0xa9, 0x6c, 0x56, 0xf4, 0xea, 0x65, 0x7a, 0xae, 0x08,
  0xba, 0x78, 0x25, 0x2e, 0x1c, 0xa6, 0xb4, 0xc6, 0xe8, 0xdd, 0x74, 0x1f, 0x4b, 0xbd, 0x8b, 0x8a,
  0x70, 0x3e, 0xb5, 0x66, 0x48, 0x03, 0xf6, 0x0e, 0x61, 0x35, 0x57, 0xb9, 0x86, 0xc1, 0x1d, 0x9e,
  0xe1, 0xf8, 0x98, 0x11, 0x69, 0xd9, 0x8e, 0x94, 0x9b, 0x1e, 0x87, 0xe9, 0xce, 0x55, 0x28, 0xdf,
  0x8c, 0xa1, 0x89, 0x0d, 0xbf, 0xe6, 0x42, 0x68, 0x41, 0x99, 0x2d, 0x0f, 0xb0, 0x54, 0xbb, 0x16 
};

const byte INVERSE_SBOX[256] =  {
  0x52, 0x09, 0x6a, 0xd5, 0x30, 0x36, 0xa5, 0x38, 0xbf, 0x40, 0xa3, 0x9e, 0x81, 0xf3, 0xd7, 0xfb,
  0x7c, 0xe3, 0x39, 0x82, 0x9b, 0x2f, 0xff, 0x87, 0x34, 0x8e, 0x43, 0x44, 0xc4, 0xde, 0xe9, 0xcb,
  0x54, 0x7b, 0x94, 0x32, 0xa6, 0xc2, 0x23, 0x3d, 0xee, 0x4c, 0x95, 0x0b, 0x42, 0xfa, 0xc3, 0x4e,
  0x08, 0x2e, 0xa1, 0x66, 0x28, 0xd9, 0x24, 0xb2, 0x76, 0x5b, 0xa2, 0x49, 0x6d, 0x8b, 0xd1, 0x25,
  0x72, 0xf8, 0xf6, 0x64, 0x86, 0x68, 0x98, 0x16, 0xd4, 0xa4, 0x5c, 0xcc, 0x5d, 0x65, 0xb6, 0x92,
  0x6c, 0x70, 0x48, 0x50, 0xfd, 0xed, 0xb9, 0xda, 0x5e, 0x15, 0x46, 0x57, 0xa7, 0x8d, 0x9d, 0x84,
  0x90, 0xd8, 0xab, 0x00, 0x8c, 0xbc, 0xd3, 0x0a, 0xf7, 0xe4, 0x58, 0x05, 0xb8, 0xb3, 0x45, 0x06,
  0xd0, 0x2c, 0x1e, 0x8f, 0xca, 0x3f, 0x0f, 0x02, 0xc1, 0xaf, 0xbd, 0x03, 0x01, 0x13, 0x8a, 0x6b,
  0x3a, 0x91, 0x11, 0x41, 0x4f, 0x67, 0xdc, 0xea, 0x97, 0xf2, 0xcf, 0xce, 0xf0, 0xb4, 0xe6, 0x73,
  0x96, 0xac, 0x74, 0x22, 0xe7, 0xad, 0x35, 0x85, 0xe2, 0xf9, 0x37, 0xe8, 0x1c, 0x75, 0xdf, 0x6e,
  0x47, 0xf1, 0x1a, 0x71, 0x1d, 0x29, 0xc5, 0x89, 0x6f, 0xb7, 0x62, 0x0e, 0xaa, 0x18, 0xbe, 0x1b,
  0xfc, 0x56, 0x3e, 0x4b, 0xc6, 0xd2, 0x79, 0x20, 0x9a, 0xdb, 0xc0, 0xfe, 0x78, 0xcd, 0x5a, 0xf4,
  0x1f, 0xdd, 0xa8, 0x33, 0x88, 0x07, 0xc7, 0x31, 0xb1, 0x12, 0x10, 0x59, 0x27, 0x80, 0xec, 0x5f,
  0x60, 0x51, 0x7f, 0xa9, 0x19, 0xb5, 0x4a, 0x0d, 0x2d, 0xe5, 0x7a, 0x9f, 0x93, 0xc9, 0x9c, 0xef,
  0xa0, 0xe0, 0x3b, 0x4d, 0xae, 0x2a, 0xf5, 0xb0, 0xc8, 0xeb, 0xbb, 0x3c, 0x83, 0x53, 0x99, 0x61,
  0x17, 0x2b, 0x04, 0x7e, 0xba, 0x77, 0xd6, 0x26, 0xe1, 0x69, 0x14, 0x63, 0x55, 0x21, 0x0c, 0x7d 
};

const byte PRESET_MATRIX[2][AES_STATE_COLUMN_SIZE][AES_STATE_ROW_SIZE] = {
  {
    { 0x2, 0x3, 0x1, 0x1 },
    { 0x1, 0x2, 0x3, 0x1 },
    { 0x1, 0x1, 0x2, 0x3 },
    { 0x3, 0x1, 0x1, 0x2 }
  },
  { 
    { 0xe, 0xb, 0xd, 0x9 }, 
    { 0x9, 0xe, 0xb, 0xd },
    { 0xd, 0x9, 0xe, 0xb },
    { 0xb, 0xd, 0x9, 0xe }
  }
};

const byte ROUND_CONSTANTS[11] = { 0x0, 0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x1b, 0x36 };


void aes_sub_bytes(aes_dir_t dir, byte state[AES_STATE_COLUMN_SIZE][AES_STATE_ROW_SIZE]) {
  const byte * box;
  
  if(dir == FORWARD) box = FORWARD_SBOX;
  else box = INVERSE_SBOX;
  
  for(int col=0; col < AES_STATE_COLUMN_SIZE; col++) {
    for(int row=0; row < AES_STATE_ROW_SIZE; row++) {
      state[col][row] = box[state[col][row]];
    }
  }
}


void aes_shift_rows(aes_dir_t dir, byte state[AES_STATE_COLUMN_SIZE][AES_STATE_ROW_SIZE]) {
  const byte forward_map[AES_STATE_COLUMN_SIZE][AES_STATE_ROW_SIZE] = {
    { state[0][0], state[0][1], state[0][2], state[0][3] },
    { state[1][1], state[1][2], state[1][3], state[1][0] },
    { state[2][2], state[2][3], state[2][0], state[2][1] },
    { state[3][3], state[3][0], state[3][1], state[3][2] }
  };

  const byte inverse_map[AES_STATE_COLUMN_SIZE][AES_STATE_ROW_SIZE] = {
    { state[0][0], state[0][1], state[0][2], state[0][3] },
    { state[1][3], state[1][0], state[1][1], state[1][2] },
    { state[2][2], state[2][3], state[2][0], state[2][1] },
    { state[3][1], state[3][2], state[3][3], state[3][0] }
  };

  if(dir == FORWARD)  memcpy(state, forward_map, AES_BLOCK_SIZE);
  else memcpy(state, inverse_map, AES_BLOCK_SIZE);
}


static inline byte mult_gf8(byte a, byte b) {
  byte result = 0x0;
  byte hi_bit;

  for(int bit=0; bit < BITS_IN__BYTE; bit++) {
    if(b & 0x1) result ^= a;
    
    hi_bit = a & 0x80;
    a <<= 1;

    if(hi_bit) a ^= 0x1b; // x^8 + x^4 + x^3 + x + 1 (AES irreducible polynomial)

    b >>= 1;
  }

  return result;
}


static inline void mix_columm_matrix_multiply(aes_dir_t dir, byte * s[AES_STATE_COLUMN_SIZE]) {
  byte temp[AES_STATE_COLUMN_SIZE];

  for(int i=0; i < AES_STATE_COLUMN_SIZE; i++) {
    temp[i] = 0x0;
    for(int j=0; j < AES_STATE_ROW_SIZE; j++) {
      temp[i] = add_gf8(temp[i], mult_gf8(PRESET_MATRIX[dir][i][j], *s[j]));
    } 
  }

  *s[0] = temp[0];
  *s[1] = temp[1];
  *s[2] = temp[2];
  *s[3] = temp[3];
}


void aes_mix_columns(aes_dir_t dir, byte state[AES_STATE_COLUMN_SIZE][AES_STATE_ROW_SIZE]) {
  byte * state_column[AES_STATE_COLUMN_SIZE];

  for(int column=0; column < AES_STATE_COLUMN_SIZE; column++) {
    state_column[0] = &state[0][column];
    state_column[1] = &state[1][column];
    state_column[2] = &state[2][column];
    state_column[3] = &state[3][column];

    // Column transformation
    mix_columm_matrix_multiply(dir, state_column);
  }
}


void aes_add_round_key(byte round_key[AES_STATE_COLUMN_SIZE][AES_STATE_ROW_SIZE], byte state[AES_STATE_COLUMN_SIZE][AES_STATE_ROW_SIZE]) {
  for(int col=0; col < AES_STATE_COLUMN_SIZE; col++) {
    for(int row=0; row < AES_STATE_ROW_SIZE; row++) {
      state[col][row] ^= round_key[col][row];
    }
  }
}


static inline void g(byte word[AES_WORD_SIZE], const uint8_t round) {
  // RotWord + SubWord + Rcon
  byte temp128 = word[0];
  word[0] = FORWARD_SBOX[word[1]] ^ ROUND_CONSTANTS[round];
  word[1] = FORWARD_SBOX[word[2]];
  word[2] = FORWARD_SBOX[word[3]];
  word[3] = FORWARD_SBOX[temp128];
}


void aes_key_expansion(const uint16_t key_len, byte round_key[AES_STATE_COLUMN_SIZE][AES_STATE_ROW_SIZE], const uint8_t round) {
  byte temp_w128[AES_WORD_SIZE];

  switch(key_len) {
    case 256: // WIP
    case 192: // WIP
    default: 
      // w4 = g(w3) + w0
      // w5 = g(w3) + w0 + w1
      // w6 = g(w3) + w0 + w1 + w2
      // w7 = g(w3) + w0 + w1 + w2 + w3

      temp_w128[0] = round_key[0][3];
      temp_w128[1] = round_key[1][3];
      temp_w128[2] = round_key[2][3];
      temp_w128[3] = round_key[3][3];

      g(temp_w128, round);

      round_key[0][0] ^= temp_w128[0];
      round_key[1][0] ^= temp_w128[1];
      round_key[2][0] ^= temp_w128[2];
      round_key[3][0] ^= temp_w128[3];

      for(int w=1; w < AES_STATE_COLUMN_SIZE; w++) {
        round_key[0][w] ^= round_key[0][w-1];
        round_key[1][w] ^= round_key[1][w-1];
        round_key[2][w] ^= round_key[2][w-1];
        round_key[3][w] ^= round_key[3][w-1];
      }
      break;
  }
}


void aes_inverse_cipher_block(const aes_ctx_t ctx, const byte cipher[AES_BLOCK_SIZE], byte input[AES_BLOCK_SIZE]) {
  uint8_t round = ctx.rounds;
  byte state[AES_STATE_COLUMN_SIZE][AES_STATE_ROW_SIZE];
  byte round_key[AES_STATE_COLUMN_SIZE][AES_STATE_ROW_SIZE];
  byte precomputed_round_keys[AES_MAX_ROUNDS + 1][AES_STATE_COLUMN_SIZE][AES_STATE_ROW_SIZE];
  
  load_state(cipher, state);
  load_state(ctx.key, round_key);
  memcpy(precomputed_round_keys[0], round_key, AES_BLOCK_SIZE);

  // Precompute round keys
  for(int r=1; r <= AES_MAX_ROUNDS; r++) {
    if(r <= ctx.rounds) {
      aes_key_expansion(ctx.key_len, round_key, r);
      memcpy(precomputed_round_keys[r], round_key, AES_BLOCK_SIZE);
    }
    else memset(precomputed_round_keys[r], 0x0, AES_BLOCK_SIZE);
  }

  // Initial transformation
  aes_add_round_key(precomputed_round_keys[round], state);

  // Rounds
  while(--round > 0) {
    aes_shift_rows(INVERSE, state);
    aes_sub_bytes(INVERSE, state);
    aes_add_round_key(precomputed_round_keys[round], state);
    aes_mix_columns(INVERSE, state);
  };

  // Last round
  aes_shift_rows(INVERSE, state);
  aes_sub_bytes(INVERSE, state);
  aes_add_round_key(precomputed_round_keys[0], state);

  store_state(state, input);
}


void aes_cipher_block(const aes_ctx_t ctx, const byte input[AES_BLOCK_SIZE], byte cipher[AES_BLOCK_SIZE]) {
  uint8_t round = 1;
  byte state[AES_STATE_COLUMN_SIZE][AES_STATE_ROW_SIZE], round_key[AES_STATE_COLUMN_SIZE][AES_STATE_ROW_SIZE];

  load_state(input, state);
  load_state(ctx.key, round_key);

  // Initial transformation
  aes_add_round_key(round_key, state);

  // Rounds
  do {
    aes_sub_bytes(FORWARD, state);
    aes_shift_rows(FORWARD, state);
    aes_mix_columns(FORWARD, state);
    aes_key_expansion(ctx.key_len, round_key, round);
    aes_add_round_key(round_key, state);
    round++;
  } while(round < ctx.rounds);

  // Last round
  aes_sub_bytes(FORWARD, state);
  aes_shift_rows(FORWARD, state);
  aes_key_expansion(ctx.key_len, round_key, round);
  aes_add_round_key(round_key, state);

  store_state(state, cipher);
}
