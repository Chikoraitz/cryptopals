#include <stdio.h>
#include <stdlib.h>

#include "cmocka_api.h"

#include "../include/utils/data_conversion.h"

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

int main(void) {
  const struct CMUnitTest tests[] = {
    cmocka_unit_test(validate_raw_bytes)
  };

  return cmocka_run_group_tests(tests, NULL, NULL);
}