#include <stdio.h>
#include <stdlib.h>

#include "cmocka_api.h"

#include "../include/set1/base64.h"
#include "../include/set1/fixed_xor.h"
#include "../include/set1/single_byte_xor_cipher.h"
#include "../include/set1/break_repeating_key_xor.h"


/**
 * Challenge 1:
 * Convert binary in hex format into base64 format 
*/
void validate_challenge1(void ** state) {
  (void) state; // Unused
  enum { N_TESTS = 5, BUFFER_SIZE = 100 };

  char b64_buffer[BUFFER_SIZE];
  byte byte_buffer[BUFFER_SIZE] = {0x0};
  char plaintext_buffer[BUFFER_SIZE];

  const char * test_cases_hexstr[] = {
    "414243", "41424344", "4546474849", "4a4b4c4d4e4f",
    "49276d206b696c6c696e6720796f757220627261696e206c696b65206120706f69736f6e6f7573206d757368726f6f6d"
  };

  const char * test_cases_b64[] = {
    "QUJD", "QUJDRA==", "RUZHSEk=", "SktMTU5P",
    "SSdtIGtpbGxpbmcgeW91ciBicmFpbiBsaWtlIGEgcG9pc29ub3VzIG11c2hyb29t"
  };

  const char * test_cases_plaintext[] = {
    "ABC", "ABCD", "EFGHI", "JKLMNO", 
    "I'm killing your brain like a poisonous mushroom"
  };

  for(int i=0; i < N_TESTS; i++) {
    // Base64 encoding tests
    hexstr_to_bytes(test_cases_hexstr[i], byte_buffer);
    bytes_to_base64(byte_buffer, b64_buffer, strlen(test_cases_hexstr[i]) / NIBBLE_BYTE);
    assert_string_equal(b64_buffer, test_cases_b64[i]);

    // base64_to_bytes(b64_buffer, plaintext_buffer);
    // assert_string_equal(plaintext_buffer, test_cases_plaintext[i]);
  }
}


/**
 * Challenge 2:
 * One-time pad XOR encryption
*/
void validate_challenge2(void ** state) {
  (void) state; // Unused
  enum { BUFFER_SIZE = 50, BYTE_OPERAND_SIZE = 18 };

  const char xor_hexstr1[] = "1c0111001f010100061a024b53535009181c";
  const char xor_hexstr2[] = "686974207468652062756c6c277320657965";
  char hexstr_result[BUFFER_SIZE];

  byte xor_bytes_op1[BUFFER_SIZE] = {0x0};
  byte xor_bytes_op2[BUFFER_SIZE] = {0x0};
  byte xor_bytes_result[BUFFER_SIZE] = {0x0};

  ByteData xor_op1 = {
    .size = BUFFER_SIZE,
    .content = xor_bytes_op1
  };

  ByteData xor_op2  = {
    .size = BUFFER_SIZE,
    .content = xor_bytes_op2
  };

  ByteData xor_result = {
    .size = BUFFER_SIZE,
    .content = xor_bytes_result
  };

  hexstr_to_bytes(xor_hexstr1, xor_bytes_op1);
  hexstr_to_bytes(xor_hexstr2, xor_bytes_op2);

  xor(xor_op1, xor_op2, &xor_result);

  bytes_to_hexstr(xor_bytes_result, hexstr_result, BYTE_OPERAND_SIZE);
  assert_string_equal(hexstr_result, "746865206b696420646f6e277420706c6179");
}


/**
 * Challenge 3:
 * Single-byte XOR cipher decryption
*/
void validate_challenge3(void ** state) {
  (void) state; // Unused
  enum { MSG_BUFFER_SIZE = 200 };
  const char ciphertext_hexstr[] = "1b37373331363f78151b7f2b783431333d78397828372d363c78373e783a393b3736";
  byte ciphertext_bytes[100] = {0x0};

  char best_text_buffer[MSG_BUFFER_SIZE];
  byte key_buffer[1] = {0x0};

  const ByteData cipherbytes = {
    .size = strlen(ciphertext_hexstr) / NIBBLE_BYTE,
    .content = ciphertext_bytes
  };

  ByteData msg_data = {
    .size = cipherbytes.size,
    .content = best_text_buffer
  };

  ByteData key_data = {
    .size = 1,
    .content = key_buffer
  };

  LanguageScore best = {
    .score = 300.0, // Arbitrarily large value
    .decrypted = &msg_data,
    .key = &key_data
  };

  assert_double_equal(en_score("aaaaAAAA", 8), 86.155, 0.1);
  assert_double_equal(en_score("abab ABAB", 9), 112.06, 0.1);
  assert_double_equal(en_score("aBe abE ABe AbE", 15), 79.99, 0.1);
  assert_double_equal(en_score("Timed voice share led his widen noisy young", 43), 18.30, 0.1);
  assert_double_equal(en_score("A chi-squared test is a statistical hypothesis test used in the analysis of contingency tables when the sample sizes are large.", 127), 39.33, 0.1);

  hexstr_to_bytes(ciphertext_hexstr, ciphertext_bytes);
  single_xor_decrypt(cipherbytes, &best);

  assert_int_equal(*best.key->content, 0x58);
  assert_string_equal(best.decrypted->content, "Cooking MC's like a pound of bacon");
}

// /**
//  * Challenge 4:
//  * Detect single-character XOR ciphers
// */
// void validate_challenge4(void ** state) {
//   (void) state;

//   // All ciphers have size 30 bytes, so their hex string representation will have 60
//   char cipher[60];
//   char msg[30];

//   FILE * fp; 
//   const char * filename = "../../assets/set1/4.txt";

//   if((fp = fopen(filename, "r")) == NULL) {
//     printf("Can't open file: %s\n", filename);
//     assert_true(0x0);
//   }

//   const int error = detect_single_byte_key_xor(fp, cipher, msg);

//   assert_int_equal(error, 0x0);
//   assert_string_equal(cipher, "7b5a4215415d544115415d5015455447414c155c46155f4058455c5b523f");
//   assert_string_equal(msg, "Now that the party is jumping\n");

//   fclose(fp);
// }


// /**
//  * Challenge 5:
//  * Implementation of Repeating-key XOR
// */
// void validate_challenge5(void ** state) {
//   (void) state;

//   const char * key = "ICE";
//   const int key_size = strlen(key);

//   const char * msg = "Burning 'em, if you ain't quick and nimble\nI go crazy when I hear a cymbal";
//   const int msg_size = strlen(msg);

//   const char * result = "0b3637272a2b2e63622c2e69692a23693a2a3c6324202d623d63343c2a26226324272765272a282b2f20430a652e2c652a3124333a653e2b2027630c692b20283165286326302e27282f"; 
//   char msg_encrypted_hex[msg_size * NIBBLE_BYTE];

//   Data * byte_text = allocate_bytes(msg_size);
//   Data * byte_key = allocate_bytes(key_size);
//   Data * msg_encrypted = allocate_bytes(msg_size);

//   strncpy(byte_text->content, msg, byte_text->size);
//   strncpy(byte_key->content, key, byte_key->size);

//   xor(msg_encrypted, byte_text, byte_key);
//   bytes_to_hexstr(msg_encrypted_hex, msg_encrypted);

//   assert_int_equal(strlen(msg_encrypted_hex), strlen(result));
//   assert_string_equal(msg_encrypted_hex, result);

//   deallocate(byte_text);
//   deallocate(byte_key);
//   deallocate(msg_encrypted);
// }


// /**
//  * Challenge 6:
//  * Break Repeating-Key XOR
// */
// void validate_challenge6(void ** state) {
//   (void) state;

//   // FILE * fp;
//   // const char * filename = "../../assets/set1/6.txt";

//   // if((fp = fopen(filename, "r")) == NULL) {
//   //   printf("Can't open file: %s\n", filename);
//   //   assert_true(0x0);
//   // }

//   // // [WIP] Read msg from file and base64 decode it
//   // decode_base64(decoded_encrypted_msg, base64_encrypted_msg);
//   // // *****

//   // // [WIP] Change from string to Data data format
//   // assert_int_equal(edit_distance("this is a test", "wokka wokka!!"), -1);
//   // assert_int_equal(edit_distance("this is a test", "wokka wokka!!!"), 37);

//   // // [WIP] Guess the XOR key size
//   // const int keysize = guess_xor_keysize(decoded_encrypted_msg);
//   // assert_int_equal(keysize, 0x0); 

//   // // [WIP] Break repeating key
//   // repeating_xor_decrypt(decoded_encrypted_msg, keysize);

//   // assert_string_equal(key, "");
//   // assert_string_equal(msg, "");
// }


int main(void) {
  const struct CMUnitTest tests[] = {
    cmocka_unit_test(validate_challenge1),
    cmocka_unit_test(validate_challenge2),
    cmocka_unit_test(validate_challenge3),
    // cmocka_unit_test(validate_challenge4),
    // cmocka_unit_test(validate_challenge5),
    // cmocka_unit_test(validate_challenge6)
  };

  return cmocka_run_group_tests(tests, NULL, NULL);
}