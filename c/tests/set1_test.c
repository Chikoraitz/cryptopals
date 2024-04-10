#include "../include/set1/utils.h"
#include "../include/set1/base64.h"
#include "../include/set1/fixed_xor.h"

#include "cmocka_api.h"


void validate_hexchars2bytevalue_conversion(void ** state) {
  (void) state; // Unused

  assert_int_equal(convertHexChars2Byte('4','2'), 0x42);
  assert_int_equal(convertHexChars2Byte('0','9'), 0x09);
  assert_int_equal(convertHexChars2Byte('2','0'), 0x20);
  assert_int_equal(convertHexChars2Byte('0','e'), 0x0e);
  assert_int_equal(convertHexChars2Byte('2','a'), 0x2a);
}


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


void validate_challenge2(void ** state) {
  (void) state; // Unused

  assert_string_equal(xor("1c0111001f010100061a024b53535009181c", "686974207468652062756c6c277320657965"), "746865206b696420646f6e277420706c6179");
}


int main(void) {
  const struct CMUnitTest tests[] = {
    cmocka_unit_test(validate_hexchars2bytevalue_conversion),
    cmocka_unit_test(validate_challenge1),
    cmocka_unit_test(validate_challenge2)
  };

  return cmocka_run_group_tests(tests, NULL, NULL);
}