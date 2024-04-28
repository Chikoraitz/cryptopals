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
 * xor_decrypt() - Brute-force of the XOR-encrypted message.
 * @msg:          Decrypted message content
 * @encrypt_msg:  XOR-encrypted message
 * @key_size:     Key size subject to brute force
 * 
 * This function brute-forces the XOR key based on the key size provided.
 * The key size will determine the complete set of possible XOR keys used 
 * to encrypt the message.
*/
void xor_decrypt(LanguageScore * msg, const Data encrypt_msg, const int key_size) {
  byte is_new_key;

  LanguageScore try = {
    .score = 100.0,
    .text.content = (byte *) malloc(sizeof(byte *) * msg->text.size),
    .text.size = msg->text.size,
    .key = (byte *) malloc(sizeof(byte *) * key_size)
  };

  Data xor_key = {
    .size = key_size,
    .content = (byte *) malloc(sizeof(byte) * xor_key.size)
  };

  memset(xor_key.content, 0, key_size); // Initial key: 0x00

  do {
    xor(&try.text, encrypt_msg, xor_key);

    // Get the plaintext message and evaluate its language score
    memcpy(try.key, xor_key.content, key_size);
    score_assessment(msg, &try, try.text.size, key_size);

    // Checks if the 0x00 key is generated again and exits the loop
    is_new_key = generate_next_key_try(xor_key.content, key_size);

  } while(is_new_key);

  free(xor_key.content);
  free(try.text.content);
  free(try.key);
}


/**
 * generate_next_key_try() - Generates the next XOR key to be tested against the XOR-encrypted message.
 * @buffer: Key byte array content
 * @size:   Size of the key byte array
 * 
 * Single increments of raw byte array value. To avoid having to be restricted to
 * the maximum values defined by C, it handles each byte independently. Hence, it
 * updates increasingly larger significant bytes by detecting its overflow -
 * similar to how a low-level register keeps track of values in counters.
 * 
 * Return:
 * @new:    Handler that indicates if the new key generated has not already been tested.
 *          Brute-force loop ending criteria.  
*/
static byte generate_next_key_try(byte * buffer, const int size) {
  byte new = 0;

  buffer[LSB(size)]++;

  // Iterate from least significant byte to most significant byte
  for(int i=LSB(size); i >= MSB; i--) {
    // Checks if the new generated key is 0x00 meaning that all combinations were exhausted
    new |= buffer[i];

    // Detect overflows
    if(buffer[i] == 0x00 && i != MSB) buffer[i-1]++;
    else break;
  }

  return new;
}


/**
 * score_assessment() - English text score assessment
 * @best:           Message that is most likely to be English text   
 * @try:            Next iterated message
 * @content_size:   Message size
 * @key_size:       Size of the key byte array
 * 
 * Compares the plaintext try with the most likely plaintext to be an English
 * sentence. The closest the score is to 0, the closest it is from the expected 
 * character frequency, the most liekly it is to be an English sentence.
*/
static void score_assessment(LanguageScore * best, LanguageScore * try, const int text_size, const int key_size) {  
  try->score = en_score(try->text.content);

  if(try->score < best->score) {
      best->score = try->score;
      memcpy(best->text.content, try->text.content, text_size);
      memcpy(best->key, try->key, key_size);
  }
}


/**
 * en_score() - Chi-squared English score
 * @plaintext_msg:  English message subject to evaluation 
 * 
 * The score compilation is based on the Pearson's chi-squared value.
 * This means that the smaller the score, the more closely the decrypted
 * message resembles an English sentence.
 * https://en.wikipedia.org/wiki/Chi-squared_test
 * 
 * Return: 
 * @chi_test: Chi-square calculation
*/
double en_score(const char * plaintext_msg) {
  const int string_size = strlen(plaintext_msg);
  
  // Alphabet letters + non-alphabetic characters (e.g., number, punctuation, etc..)  
  int string_freq[ALPHABET_SIZE + 1] = { 0 };
  double chi_test = 0.0;
  double delta, freq_obs;
  char c;

  // Character frequency distribution
  for(int i=0; i < string_size; i++) {
    c = plaintext_msg[i];
    if(c >= 'A' && c <= 'Z') string_freq[c - 'A']++;
    else {
      if(c >= 'a' && c <= 'z') string_freq[c - 'a']++;
      else string_freq[ALPHABET_SIZE]++;
    }    
  }

  // Sentence chi-test calculation 
  for(int i=0; i < ALPHABET_SIZE; i++) {
    freq_obs = string_freq[i] / (double) string_size;
    delta = freq_obs - freq_expected[i]; 
    chi_test += delta * delta / freq_expected[i]; 
  }

  return chi_test;
}