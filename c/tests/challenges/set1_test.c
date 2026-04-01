#include "../cmocka_api.h"

#include "../../include/challenges/set1.h"

/**
 * Challenge 1:
 * Convert binary in hex format into base64 format 
*/
void validate_challenge1(void ** state) {
  (void) state; // Unused
  const char input[] = "49276d206b696c6c696e6720796f757220627261696e206c696b65206120706f69736f6e6f7573206d757368726f6f6d";
  char result[200];
  
  c1(input, result);
  assert_string_equal(
    result,
    "SSdtIGtpbGxpbmcgeW91ciBicmFpbiBsaWtlIGEgcG9pc29ub3VzIG11c2hyb29t"
  );  
}

/**
 * Challenge 2:
 * One-time pad XOR encryption
*/
void validate_challenge2(void ** state) {
  (void) state; // Unused
  char result[200];
  c2(
    "1c0111001f010100061a024b53535009181c",
    "686974207468652062756c6c277320657965",
    result
  );
  assert_string_equal(result, "746865206b696420646f6e277420706c6179");
}


/**
 * Challenge 3:
 * Single-byte XOR cipher decryption
*/
void validate_challenge3(void ** state) {
  (void) state; // Unused
  char msg[200];
  c3("1b37373331363f78151b7f2b783431333d78397828372d363c78373e783a393b3736", msg);
  assert_string_equal(msg, "Cooking MC's like a pound of bacon");
}

/**
 * Challenge 4:
 * Detect single-character XOR ciphers
*/
void validate_challenge4(void ** state) {
  (void) state;
  char cipher_hexstr[61];
  c4("../../assets/set1/4.txt", cipher_hexstr);
  assert_string_equal(cipher_hexstr, "7b5a4215415d544115415d5015455447414c155c46155f4058455c5b523f");
}


/**
 * Challenge 5:
 * Implementation of Repeating-key XOR
*/
void validate_challenge5(void ** state) {
  (void) state;
  const char * plaintext = "Burning 'em, if you ain't quick and nimble\nI go crazy when I hear a cymbal";
  const char * key = "ICE";
  char cipher_hexstr[strlen(plaintext) * NIBBLE_BYTE];
  
  c5(plaintext, key, cipher_hexstr);
  assert_string_equal(
    cipher_hexstr,
    "0b3637272a2b2e63622c2e69692a23693a2a3c6324202d623d63343c2a26226324272765272a282b2f20430a652e2c652a3124333a653e2b2027630c692b20283165286326302e27282f"
  );
}


/**
 * Challenge 6:
 * Break Repeating-Key XOR
*/
void validate_challenge6(void ** state) {
  (void) state;
  const char * filepath = "../../assets/set1/6.txt";
  char key[100];

  c6(filepath, key);
  assert_string_equal(key, "Terminator X: Bring the noise");
}


/**
 * Challenge 7:
 * AES in ECB mode
 */
void validate_challenge7() {
  enum { LINE_BUFFER_SIZE = 70, BUFFER_SIZE = 3000 };
  
  const char * filename = "../../assets/set1/7.txt";
  byte key[AES_BLOCK_SIZE] = "YELLOW SUBMARINE";
  char plaintext[BUFFER_SIZE];
  FILE * fp = fopen("../../assets/set1/7-solution.txt", "rb");
  
  byte result[BUFFER_SIZE] = {0x0};
  size_t bytes_read;
  
  if(fp) {
    bytes_read = fread(result, 1, BUFFER_SIZE - 1, fp);
    result[bytes_read] = 0;
    fclose(fp);
  }
  else printf("Can't open file: %s\n", "7-solution.txt");

  if(c7(filename, plaintext, key) == AES_OK) {
    for(int b=0; b < bytes_read; b++) {
      assert_int_equal(plaintext[b], result[b]);
    }
  }
  else assert_false(0);
}


/**
 * Challenge 8:
 * Detect AES in ECB mode
 */
void validate_challenge8() {
  const char * result = "d880619740a8a19b7840a8a31c810a3d08649af70dc06f4fd5d2d69c744cd283e2dd052f6b641dbf9d11b0348542bb5708649af70dc06f4fd5d2d69c744cd2839475c9dfdbc1d46597949d9c7e82bf5a08649af70dc06f4fd5d2d69c744cd28397a93eab8d6aecd566489154789a6b0308649af70dc06f4fd5d2d69c744cd283d403180c98c8f6db1f2a3f9c4040deb0ab51b29933f2c123c58386b06fba186a";
  char ecb_detected[322];
  c8("../../assets/set1/8.txt", ecb_detected);
  assert_string_equal(ecb_detected, result);
}


int main(void) {
  const struct CMUnitTest tests[] = {
    cmocka_unit_test(validate_challenge1),
    cmocka_unit_test(validate_challenge2),
    cmocka_unit_test(validate_challenge3),
    cmocka_unit_test(validate_challenge4),
    cmocka_unit_test(validate_challenge5),
    cmocka_unit_test(validate_challenge6),
    cmocka_unit_test(validate_challenge7),
    cmocka_unit_test(validate_challenge8)
  };

  return cmocka_run_group_tests(tests, NULL, NULL);
}