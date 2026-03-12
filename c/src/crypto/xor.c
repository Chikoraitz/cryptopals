#include "../../include/crypto/xor.h"

void xor(const ByteStream in_op1, const ByteStream in_op2, ByteStream * out) {
  for(int i=0; i<out->size; i++) {
    out->content[i] = in_op1.content[i % in_op1.size] ^ in_op2.content[i % in_op2.size];
  }
}


void single_xor_decrypt(const ByteStream cipher, LanguageScore * out) {
  // Scope variables
  enum { MSG_BUFFER_SIZE = 200 };
  double score;
  
  // Buffers
  char try_text[MSG_BUFFER_SIZE];
  byte key_buffer[1] = {0x0};

  // Initializations
  LanguageScore try = {
    .score = 100.0,
    .decrypted = &(ByteStream) { .size = out->decrypted->size, .content = try_text },
    .key = &(ByteStream) { .size = 1, .content = key_buffer },
  };

  for(uint8_t key=0x00; key<0xff; key++) {
    *try.key->content = key;
    xor(cipher, *try.key, try.decrypted);

    // Assess XORed message
    try.score = en_score(try.decrypted->content, try.decrypted->size);
    
    if(try.score < out->score) {
      out->score = try.score;
      strncpy(out->decrypted->content, try.decrypted->content, out->decrypted->size);
      out->decrypted->content[out->decrypted->size] = '\0';
      *out->key->content = *try.key->content;
    } 
  }
}


int guess_xor_keysize(const ByteStream cipher, const int LOWER_BOUND, const int UPPER_BOUND) {
  int best_guess = LOWER_BOUND;
  int best_score = 500; // Arbitrarily large
  int temp_distance, score, n_blocks;
  ByteStream stream;

  for(int keysize=LOWER_BOUND; keysize<UPPER_BOUND; keysize++) {
    
  }
  
  return best_guess;
}