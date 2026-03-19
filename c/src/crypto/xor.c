#include "../../include/crypto/xor.h"

void xor(const ByteStream in_op1, const ByteStream in_op2, ByteStream * out) {
  for(int i=0; i<out->size; i++) {
    out->content[i] = in_op1.content[i % in_op1.size] ^ in_op2.content[i % in_op2.size];
  }
}


void single_xor_decrypt(const ByteStream cipher, LanguageScore * out, const float threshold) {  
  char try_text[out->decrypted->size];
  byte key_buffer[1] = {0x0};
  LanguageScore try = LANGUAGE_SCORE(try_text, out->decrypted->size, key_buffer, 1);

  for(uint8_t key=0x00; key<0xff; key++) {
    *try.key->content = key;
    xor(cipher, *try.key, try.decrypted);

    // Assess XORed message
    try.score = en_score(try.decrypted->content, try.decrypted->size, threshold);
    
    if(try.score < out->score) {
      out->score = try.score;
      strncpy(out->decrypted->content, try.decrypted->content, out->decrypted->size);
      out->decrypted->content[out->decrypted->size] = '\0';
      *out->key->content = key;
    }
  }
}


int guess_xor_keysize(const ByteStream cipher, const int LOWER_BOUND, const int UPPER_BOUND, const int n_blocks) {
  ByteStream stream;
  unsigned int best_keysize_guess = LOWER_BOUND;
  unsigned int offset = 0, block_i;
  int hd;
  float score, best_score = 100.0;

  for(unsigned int keysize=LOWER_BOUND; keysize<=UPPER_BOUND; keysize++) {
    offset = 0;
    score = 0.0;
    block_i = 0;
    if(n_blocks == 0) {
      while(offset < cipher.size) {
        hd = hamming_distance(
          (ByteStream) { .size = keysize, .content = cipher.content + offset },
          (ByteStream) { .size = keysize, .content = cipher.content + offset + keysize }
        );
        offset += keysize;
        score += hd; // Score is the total hamming distance of all consecutive blocks
        block_i++;
      }
      score /= cipher.size;
    }
    else {
      for(block_i=0; block_i < n_blocks; block_i++) {
        hd = hamming_distance(
          (ByteStream) { .size = keysize, .content = cipher.content + (block_i * keysize) },
          (ByteStream) { .size = keysize, .content = cipher.content + ((block_i + 1) * keysize) }
        );
        score += hd;
      }
      // Normalization
      score /= keysize;
      score /= block_i;
    }

    // Percentage per byte
    score = (score * 100.0) / 8.0;

    if(score < best_score) {
      best_score = score;
      best_keysize_guess = keysize;
    }
  }
  
  return best_keysize_guess;
}


void transpose_vigenere_cipher(const ByteStream cipher, ByteStream * buffer, const int keysize, const int index) {
  unsigned int column = 0;
  unsigned int i = 0;
  
  for(int j=0; j < cipher.size; j++) {
    if(j % keysize == index) {
        buffer->content[i] = cipher.content[j];
        i++;
    }
  }
  buffer->size = i;
}