#include <stdio.h>
#include <stdlib.h>

#include "cmocka_api.h"

#include "../include/set1/utils.h"
#include "../include/set1/base64.h"
#include "../include/set1/fixed_xor.h"
#include "../include/set1/single_byte_xor_cipher.h"


void validate_raw_bytes(void **state) {
  (void) state; // Unused

  byte test1[1];
  import_raw_bytes(test1, "a2");
  assert_int_equal(*test1, 0xa2);

  byte test2[5];
  import_raw_bytes(test2, "139ac7ffd5");
  assert_int_equal(test2[0], 0x13);
  assert_int_equal(test2[1], 0x9a);
  assert_int_equal(test2[2], 0xc7);
  assert_int_equal(test2[3], 0xff);
  assert_int_equal(test2[4], 0xd5);
}


/**
 * Challenge 1:
 * Convert binary in hex format into base64 format 
*/
void validate_challenge1(void ** state) {
  (void) state; // Unused
  
  const char * test_cases[] = {
    "414243", "41424344", "4546474849", "4a4b4c4d4e4f",
    "49276d206b696c6c696e6720796f757220627261696e206c696b65206120706f69736f6e6f7573206d757368726f6f6d"
  };

  const char * test_expected[] = {
    "QUJD", "QUJDRA==", "RUZHSEk=", "SktMTU5P",
    "SSdtIGtpbGxpbmcgeW91ciBicmFpbiBsaWtlIGEgcG9pc29ub3VzIG11c2hyb29t"
  };

  char * res;

  for(int i=0; i < 5; i++) {
    res = (char *) malloc(sizeof(char) * get_base64_size(test_cases[i]) + 1);

    base64_from_hex_string(res, test_cases[i]);
    assert_string_equal(res, test_expected[i]);
    
    free(res);
  }
}


/**
 * Challenge 2:
 * One-time pad XOR encryption
*/
void validate_challenge2(void ** state) {
  (void) state; // Unused
  
  const char * xor_string1 = "1c0111001f010100061a024b53535009181c";
  const char * xor_string2 = "686974207468652062756c6c277320657965";  
  char * hex_result_string = (char *) malloc(sizeof(char) * strlen(xor_string1) + 1);

  Data xor_operand1 = { 
    .size = strlen(xor_string1) / NIBBLE_BYTE,
    .content = (byte *) malloc(sizeof(byte) * xor_operand1.size)
  };

  Data xor_operand2 = { 
    .size = strlen(xor_string2) / NIBBLE_BYTE,
    .content = (byte *) malloc(sizeof(byte) * xor_operand2.size)
  };

  Data xor_result = {
    .size = strlen(xor_string1) / NIBBLE_BYTE,
    .content = (byte *) malloc(sizeof(char) * xor_result.size)
  };
    
  import_raw_bytes(xor_operand1.content, xor_string1);
  import_raw_bytes(xor_operand2.content, xor_string2);

  xor(&xor_result, xor_operand1, xor_operand2);

  export_raw_bytes(hex_result_string, xor_result);
  assert_string_equal(hex_result_string, "746865206b696420646f6e277420706c6179");
  
  free(xor_operand1.content);
  free(xor_operand2.content); 
  free(xor_result.content);
  free(hex_result_string);
}


/**
 * Challenge 3:
 * Single-byte XOR cipher decryption
*/
void validate_challenge3(void ** state) {
  (void) state; // Unused
  
  assert_double_equal(en_score("aaaaAAAA", 8), 86.155, 0.1);
  assert_double_equal(en_score("abab ABAB", 9), 112.06, 0.1);
  assert_double_equal(en_score("aBe abE ABe AbE", 15), 79.99, 0.1);
  assert_double_equal(en_score("Timed voice share led his widen noisy young", 43), 18.30, 0.1);
  assert_double_equal(en_score("A chi-squared test is a statistical hypothesis test used in the analysis of contingency tables when the sample sizes are large.", 127), 39.33, 0.1);
  
  const char * encrypt_msg_string = "1b37373331363f78151b7f2b783431333d78397828372d363c78373e783a393b3736";

  Data encrypt_msg = {
    .size = strlen(encrypt_msg_string) / NIBBLE_BYTE,
    .content = (byte *) malloc(sizeof(byte) * encrypt_msg.size)
  };

  LanguageScore best = {
    .score = 100.0, // Arbitrarily large value
    .text.content = (byte *) malloc(sizeof(byte *) * encrypt_msg.size),
    .text.size = encrypt_msg.size,
    .key = (byte *) malloc(sizeof(byte *) * 1)
  };
  
  import_raw_bytes(encrypt_msg.content, encrypt_msg_string);
  xor_decrypt(&best, encrypt_msg, 1);

  assert_int_equal(*best.key, 0x58);
  assert_string_equal(best.text.content, "Cooking MC's like a pound of bacon");

  free(encrypt_msg.content);
  free(best.text.content);
  free(best.key);
}


/**
 * Challenge 4:
 * Detect single-character XOR ciphers
*/
void validate_challenge4(void ** state) {
  (void) state;

  // The ciphers all have size 30 bytes
  char cipher[60];
  char msg[60];

  FILE * fp; 
  const char * filename = "../../assets/set1/4.txt";

  if((fp = fopen(filename, "r")) == NULL) {
    printf("Can't open file: %s\n", filename);
    assert_true(0x0);
  }

  const int error = detect_single_byte_key_xor(fp, cipher, msg);

  fclose(fp);

  assert_int_equal(error, 0x0);
  assert_string_equal(cipher, "7b5a4215415d544115415d5015455447414c155c46155f4058455c5b523f");
  assert_string_equal(msg, "Now that the party is jumping\n");
}


/**
 * Challenge 5:
 * Implementation of Repeating-key XOR
*/
void validate_challenge5(void ** state) {
  (void) state;

  const char * key = "ICE";
  const int key_size = strlen(key);

  const char * msg = "Burning 'em, if you ain't quick and nimble\nI go crazy when I hear a cymbal";
  const int msg_size = strlen(msg);

  const char * result = "0b3637272a2b2e63622c2e69692a23693a2a3c6324202d623d63343c2a26226324272765272a282b2f20430a652e2c652a3124333a653e2b2027630c692b20283165286326302e27282f"; 

  char msg_encrypted_hex[msg_size * NIBBLE_BYTE];

  Data raw_text = {
    .size = msg_size,
    .content = (byte *) malloc(sizeof(byte) * msg_size)
  };

  Data raw_key = {
    .size = key_size,
    .content = (byte *) malloc(sizeof(byte) * msg_size)
  };

  Data msg_encrypted = {
    .size = raw_text.size,
    .content = (byte *) malloc(sizeof(char) * raw_text.size)
  };

  strncpy(raw_text.content, msg, raw_text.size);
  strncpy(raw_key.content, key, raw_key.size);

  xor(&msg_encrypted, raw_text, raw_key);

  export_raw_bytes(msg_encrypted_hex, msg_encrypted);

  assert_int_equal(strlen(msg_encrypted_hex), strlen(result));
  assert_string_equal(msg_encrypted_hex, result);

  free(raw_text.content);
  free(raw_key.content);
}


int main(void) {
  const struct CMUnitTest tests[] = {
    cmocka_unit_test(validate_raw_bytes),
    cmocka_unit_test(validate_challenge1),
    cmocka_unit_test(validate_challenge2),
    cmocka_unit_test(validate_challenge3),
    cmocka_unit_test(validate_challenge4),
    cmocka_unit_test(validate_challenge5),
  };

  return cmocka_run_group_tests(tests, NULL, NULL);
}