#include "../../include/set1/single_byte_xor_cipher.h"

// Source: https://www3.nd.edu/~busiforc/handouts/cryptography/letterfrequencies.html
const double freq_expected[] = {
  0.084966, // A-a
  0.020720, // B-b
  0.045388, // C-c
  0.033844, // D-d
  0.111607, // E-e
  0.018121, // F-f
  0.024705, // G-g
  0.030034, // H-h
  0.075448, // I-i
  0.001965, // J-j
  0.011016, // K-k
  0.054893, // L-l
  0.030129, // M-m
  0.066544, // N-n
  0.071635, // O-o
  0.031671, // P-p
  0.001962, // Q-q
  0.075809, // R-r
  0.057351, // S-s
  0.069509, // T-t
  0.036308, // U-u
  0.010074, // V-v
  0.012899, // W-w
  0.002902, // X-x
  0.017779, // Y-y
  0.002722, // Z-z
};


/**
 * The score compilation is based on the Pearson's chi-squared value.
 * This means that the smaller the score, the more closely the decrypted
 * message resembles an English sentence.
 * https://en.wikipedia.org/wiki/Chi-squared_test
 * 
 * Return: 
 * @chi_test: Chi-square calculation
*/
double en_score(const char * plaintext_msg, const int text_len) {
  int char_freq[ALPHABET_SIZE + 1] = { 0 };
  int alphabetic_len;
  double chi_test, delta, freq_exp;
  char c;

  // Character frequency distribution
  for(int i=0; i < text_len; i++) {
    c = plaintext_msg[i];
    if(c >= 'A' && c <= 'Z') { 
      char_freq[c - 'A']++;              // Uppercase A-Z
    }
    else if(c >= 'a' && c <= 'z') {      // Lowercase a-z
      char_freq[c - 'a']++;
    }
    else if(c >= 32 && c <= 126) { 
      char_freq[ALPHABET_SIZE]++;        // Other printable ASCII like numbers and punctuation - ignored
    }
    else if(c == 9 || c == 10 || c == 13) { 
      char_freq[ALPHABET_SIZE]++;        // TAB, CR, LF - ignored
    }
    // Non-printable ASCII - return an arbitrarily long value
    else return 1000.0;                  
  }

  // If the ratio of non-alphabetic characters is higher than
  // a certain threshold, it is unlikely to be an English sentence
  if((char_freq[ALPHABET_SIZE] / (double) text_len) > 0.3) return 100.0;

  chi_test = 0.0;
  alphabetic_len = text_len - char_freq[ALPHABET_SIZE];

  // Chi-test calculation of a probable English sentence 
  for(int i=0; i < ALPHABET_SIZE; i++) {
    freq_exp = freq_expected[i] * alphabetic_len;
    delta = char_freq[i] - freq_exp;
    chi_test += delta * delta / freq_exp; 
  }

  return chi_test;
}


void single_xor_decrypt(const ByteData cipher, LanguageScore * out) {
  enum { MSG_BUFFER_SIZE = 200 };
  char try_text[MSG_BUFFER_SIZE];
  byte key_buffer[1] = {0x0};
  double score;

  ByteData key_data = {
    .size = 1,
    .content = key_buffer
  };

  ByteData xored_msg = {
    .size = out->decrypted->size,
    .content = try_text
  };

  LanguageScore try = {
    .score = 100.0,
    .decrypted = &xored_msg,
    .key = &key_data
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
      // printf("%s, length: %d\n", out->decrypted->content, strlen(out->decrypted->content));
      *out->key->content = *try.key->content;
    } 
  }
}


// /**
//  * detect_single_key_xor_from() - Detects a cipher encrypted by a single-byte 
//  * key XOR from a list of ciphers located in a file
//  * @fp:         Pointer to file where the list of ciphers is located
//  * @cipher:     Single-byte XOR-encrypted cipher detected in its hexadecimal representation 
//  * @msg:        Decrypted message
//  *  
//  * Iterates over all 256 XOR-decrypted messages of all XOR-encrypted ciphers from the text file
//  * and computes the chi-square calculation for all possibilities. The most likely decryption 
//  * estimation has the lowest score (closest to zero).   
//  * 
//  * Return:
//  * @(int):      Status code
// */
// int detect_single_byte_key_xor_legacy(FILE * fp, char * cipher, char * msg) {
//   // All ciphers present in the text file have 30 bytes and are separated by a newline character
//   Data * buffer = allocate_bytes(30);    
//   const int cstr_size = buffer->size * NIBBLE_BYTE; 
//   char fstr[cstr_size + 1];

//   LanguageScore cipher_best = {
//     .score = 100.0, // Arbitrarily large value
//     .text = allocate_bytes(buffer->size),
//     .key = (byte *) malloc(sizeof(byte *))
//   };

//   LanguageScore file_best = {
//     .score = 100.0, // Arbitrarily large value
//     .text = allocate_bytes(buffer->size),
//     .key = (byte *) malloc(sizeof(byte *))
//   };

//   while(fgets(fstr, cstr_size + 1, fp) != NULL) {
//     // Remove new line characters
//     fstr[strcspn(fstr, "\n")] = '\0';
//     hexstr_to_bytes(buffer->content, fstr);

//     cipher_best.score = 100.0; // Arbitrarily large value
//     single_xor_decrypt(&cipher_best, buffer);
    
//     if(cipher_best.score < file_best.score) {
//       file_best.score = cipher_best.score;
//       memcpy(file_best.text->content, cipher_best.text->content, buffer->size);
//       memcpy(file_best.key, cipher_best.key, 1);
//       strncpy(cipher, fstr, cstr_size + 1);
//     }
//   }

//   strncpy(msg, file_best.text->content, buffer->size);


//   deallocate(buffer);
//   deallocate(cipher_best.text);
//   deallocate(file_best.text);
//   free(cipher_best.key);
//   free(file_best.key);

//   return 0;
// }
