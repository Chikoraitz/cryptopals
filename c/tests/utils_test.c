#include <stdio.h>
#include <stdlib.h>

#include "cmocka_api.h"

#include "../include/utils/data_conversion.h"
#include "../include/utils/base64.h"


void validate_hexstr_to_bytes_conversion(void **state) {
  (void) state; // Unused

  byte test1[1];
  hexstr_to_bytes("a2", &(ByteStream) { .content = test1, .size = 1});
  assert_int_equal(*test1, 0xa2);

  byte test2[5];
  hexstr_to_bytes("139ac7ffd5", &(ByteStream) { .content = test2, .size = 5});
  assert_int_equal(test2[0], 0x13);
  assert_int_equal(test2[1], 0x9a);
  assert_int_equal(test2[2], 0xc7);
  assert_int_equal(test2[3], 0xff);
  assert_int_equal(test2[4], 0xd5);
}


void validate_base64_encoding_ascii() {
  enum { N_TESTS = 5, BUFFER_SIZE = 100 };

  char b64_buffer[BUFFER_SIZE];
  byte byte_buffer[BUFFER_SIZE] = {0x0};
  byte plaintext_buffer[BUFFER_SIZE] = {0x0};
  
  ByteStream byte_stream = {
    .content = byte_buffer
  };

  ByteStream plaintext = {
    .content = plaintext_buffer
  };

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

  // Base64 encoding tests for ASCII content
  for(int i=0; i < N_TESTS; i++) {
    byte_stream.size = strlen(test_cases_hexstr[i]) / NIBBLE_BYTE;
    hexstr_to_bytes(test_cases_hexstr[i], &byte_stream);
    bytes_to_base64(byte_stream, b64_buffer);
    assert_string_equal(b64_buffer, test_cases_b64[i]);

    base64_to_bytes(b64_buffer, &plaintext);
    assert_string_equal(plaintext.content, test_cases_plaintext[i]);
  }
}


void validate_base64_encoding_non_ascii() {
    enum { N_TESTS = 3, BUFFER_SIZE = 100 };

  const char * test_b64[] = {
    "HUIfTQsPAh9PE048GmllH0kcDk4TAQsHThsBFkU2AB4BSWQgVB0dQzNTTmVS",
    "BgBHVBwNRU0HBAxTEjwMHghJGgkRTxRMIRpHKwAFHUdZEQQJAGQmB1MANxYG",
    "DBoXQR0BUlQwXwAgEwoFR08SSAhFTmU+Fgk4RQYFCBpGB08fWXh+amI2DB0P"
  };
  const char * test_hexstr[] = {
    "1d421f4d0b0f021f4f134e3c1a69651f491c0e4e13010b074e1b01164536001e01496420541d1d4333534e6552",
    "060047541c0d454d07040c53123c0c1e08491a09114f144c211a472b00051d4759110409006426075300371606",
    "0c1a17411d015254305f0020130a05474f124808454e653e160938450605081a46074f1f59787e6a62360c1d0f"
  };

  byte test_byte_buffer[BUFFER_SIZE] = {0x0};
  ByteStream test_buffer_stream = {
    .content = test_byte_buffer
  };
  
  char test_hexstr_buffer[2 * BUFFER_SIZE] = {0x0};

  for(int i=0; i<N_TESTS; i++) {
    test_buffer_stream.size = get_bytes_size_from_base64str(test_b64[i]);
    base64_to_bytes(test_b64[i], &test_buffer_stream);
    bytes_to_hexstr(test_buffer_stream, test_hexstr_buffer);
    assert_string_equal(test_hexstr_buffer, test_hexstr[i]);
  }
}


int main(void) {
  const struct CMUnitTest tests[] = {
    cmocka_unit_test(validate_hexstr_to_bytes_conversion),
    cmocka_unit_test(validate_base64_encoding_ascii),
    cmocka_unit_test(validate_base64_encoding_non_ascii)
  };

  return cmocka_run_group_tests(tests, NULL, NULL);
}