#include "cmocka_api.h"

static void smoke_test(void **state) {
  (void) state;
}


int main(void) {
  const struct CMUnitTest tests[] = {
    cmocka_unit_test(smoke_test)
  };

  return cmocka_run_group_tests(tests, NULL, NULL);
}