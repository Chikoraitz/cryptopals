#include <stdio.h>
#include <stdlib.h>

#include "cmocka_api.h"

#include "../include/set1/utils.h"
#include "../include/set1/base64.h"
#include "../include/set1/fixed_xor.h"
#include "../include/set1/single_byte_xor_cipher.h"


void validate_raw_bytes(void **state) {
  (void) state; // Unused

  byte *test1 = (byte *) malloc(sizeof(byte));
  import_raw_bytes(test1, "a2");
  assert_int_equal(*test1, 0xa2);
  free(test1);

  byte *test2 = (byte *) malloc(sizeof(byte) * 5);
  import_raw_bytes(test2, "139ac7ffd5");
  assert_int_equal(test2[0], 0x13);
  assert_int_equal(test2[1], 0x9a);
  assert_int_equal(test2[2], 0xc7);
  assert_int_equal(test2[3], 0xff);
  assert_int_equal(test2[4], 0xd5);
  free(test2);
}


/**
 * Challenge 1:
 * Convert binary in hex format into base64 format 
*/
void validate_challenge1(void ** state) {
  (void) state; // Unused

  assert_string_equal(hex2base64("414243"),"QUJD");  
  assert_string_equal(hex2base64("41424344"),"QUJDRA=="); 
  assert_string_equal(hex2base64("4546474849"),"RUZHSEk="); 
  assert_string_equal(hex2base64("4a4b4c4d4e4f"),"SktMTU5P");  
  assert_string_equal(
    hex2base64("49276d206b696c6c696e6720796f757220627261696e206c696b65206120706f69736f6e6f7573206d757368726f6f6d"),
    "SSdtIGtpbGxpbmcgeW91ciBicmFpbiBsaWtlIGEgcG9pc29ub3VzIG11c2hyb29t"
  ); 
}


/**
 * Challenge 2:
 * One-time pad XOR encryption
*/
void validate_challenge2(void ** state) {
  (void) state; // Unused
  
  SymEncryptMessage msg;
  const char * string_msg = "1c0111001f010100061a024b53535009181c";
  const char * string_key = "686974207468652062756c6c277320657965";
  raw_data xor_msg, xor_key;

  msg.data = (char *) malloc(sizeof(char) * strlen(string_msg) + 1);
  
  xor_msg.size = strlen(string_msg) / BYTE_NIBBLES;
  xor_msg.data = (byte *) malloc(sizeof(byte) * xor_msg.size);
  import_raw_bytes(xor_msg.data, string_msg);

  xor_key.size = strlen(string_key) / BYTE_NIBBLES;
  xor_key.data = (byte *) malloc(sizeof(byte) * xor_key.size);
  import_raw_bytes(xor_key.data, string_key);

  xor(&msg, xor_msg, xor_key);
  
  assert_int_equal(msg.status, Encrypted);
  assert_string_equal(msg.data, "746865206b696420646f6e277420706c6179");

  free(xor_msg.data);
  free(xor_key.data); 
  free(msg.data);
}


/**
 * Challenge 3:
 * Single-byte XOR cipher decryption
*/
void validate_challenge3(void ** state) {
  (void) state; // Unused

  const SymEncryptMessage msg_a = xor_decrypt("1b37373331363f78151b7f2b783431333d78397828372d363c78373e783a393b3736", 1);
  assert_int_equal(msg_a.status, Plaintext);
}


int main(void) {
  const struct CMUnitTest tests[] = {
    cmocka_unit_test(validate_raw_bytes),
    cmocka_unit_test(validate_challenge1),
    cmocka_unit_test(validate_challenge2),
    cmocka_unit_test(validate_challenge3)
  };

  return cmocka_run_group_tests(tests, NULL, NULL);
}