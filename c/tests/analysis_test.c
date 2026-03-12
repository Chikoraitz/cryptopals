#include "cmocka_api.h"

#include "../include/analysis/en_score.h"
#include "../include/analysis/hamming.h"


void validate_en_score(void **state) {
  (void) state;
  assert_double_equal(en_score("aaaaAAAA", 8), 86.155, 0.1);
  assert_double_equal(en_score("abab ABAB", 9), 112.06, 0.1);
  assert_double_equal(en_score("aBe abE ABe AbE", 15), 79.99, 0.1);
  assert_double_equal(en_score("Timed voice share led his widen noisy young", 43), 18.30, 0.1);
  assert_double_equal(en_score("A chi-squared test is a statistical hypothesis test used in the analysis of contingency tables when the sample sizes are large.", 127), 39.33, 0.1);
}


void validate_hamming_distance(void **state) {
  (void) state;
  char string1[] = "this is a test";
  char string2[] = "wokka wokka!!!";

  assert_int_equal(
    hamming_distance(
      (ByteStream) { .size = strlen(string1), .content = string1 },
      (ByteStream) { .size = strlen(string2), .content = string2 }
    ), 37);
}


int main(void) {
  const struct CMUnitTest tests[] = {
    cmocka_unit_test(validate_en_score),
    cmocka_unit_test(validate_hamming_distance)
  };

  return cmocka_run_group_tests(tests, NULL, NULL);
}