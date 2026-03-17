#include "../../include/crypto/xor.h"

void xor(const ByteStream in_op1, const ByteStream in_op2, ByteStream * out) {
  for(int i=0; i<out->size; i++) {
    out->content[i] = in_op1.content[i % in_op1.size] ^ in_op2.content[i % in_op2.size];
  }
}


void single_xor_decrypt(const ByteStream cipher, LanguageScore * out, const float threshold) {
  // Scope variables
  enum { MSG_BUFFER_SIZE = 200 };
  
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
    try.score = en_score(try.decrypted->content, try.decrypted->size, threshold);
    
    if(try.score < out->score) {
      out->score = try.score;
      strncpy(out->decrypted->content, try.decrypted->content, out->decrypted->size);
      out->decrypted->content[out->decrypted->size] = '\0';
      *out->key->content = key;
    }
  }
}


void single_xor_decrypt_debug(const ByteStream cipher, byte real_key, float threshold) {
  // Scope variables
  enum { MSG_BUFFER_SIZE = 200 };
  double score = 1000.0;
  
  // Buffers
  char try_text[MSG_BUFFER_SIZE];
  byte key_buffer[1] = {0x0};

  // Initializations
  LanguageScore try = {
    .decrypted = &(ByteStream) { .size = MSG_BUFFER_SIZE, .content = try_text },
    .key = &(ByteStream) { .size = 1, .content = key_buffer },
  };

  printf("\n=== START DEBUG: Key = 0x%2x", real_key);
  for(uint8_t key=0x00; key<0xff; key++) {
    *try.key->content = key;
    xor(cipher, *try.key, try.decrypted);

    // Assess XORed message
    try.score = en_score(try.decrypted->content, try.decrypted->size, threshold);
    // printf("\nKey: 0x%2x, Score: %2.1f | Decrypted msg: %s", key, try.score, try.decrypted->content);

    if(key == real_key) {
      printf("\nReal key has score: %2.1f", try.score);
    }

    if(try.score < score) {
      printf("\nLast best score: %2.1f, New best score: %2.1f | 0x%2x", score, try.score, *try.key->content);
      score = try.score;
    } 
  }
  printf("\n=== END DEBUG\n");
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