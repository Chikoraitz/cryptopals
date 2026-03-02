#include <stdio.h>
#include <stdlib.h>

#include "cmocka_api.h"

#include "../include/utils/data_conversion.h"


void validate_hexstr_to_bytes_conversion(void **state) {
  (void) state; // Unused

  byte test1[1];
  hexstr_to_bytes("a2", test1);
  assert_int_equal(*test1, 0xa2);

  byte test2[5];
  hexstr_to_bytes("139ac7ffd5", test2);
  assert_int_equal(test2[0], 0x13);
  assert_int_equal(test2[1], 0x9a);
  assert_int_equal(test2[2], 0xc7);
  assert_int_equal(test2[3], 0xff);
  assert_int_equal(test2[4], 0xd5);
}


int main(void) {
  const struct CMUnitTest tests[] = {
    cmocka_unit_test(validate_hexstr_to_bytes_conversion),
  };

  return cmocka_run_group_tests(tests, NULL, NULL);
}