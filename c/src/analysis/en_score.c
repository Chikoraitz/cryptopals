#include "../../include/analysis/en_score.h"

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
double en_score(const char * plaintext_msg, const int text_len, const float threshold) {
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
  if((char_freq[ALPHABET_SIZE] / (double) text_len) > threshold) return 500.0;

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

