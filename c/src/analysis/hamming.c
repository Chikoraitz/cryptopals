#include "../../include/analysis/hamming.h"


int hamming_distance(const ByteStream str1, const ByteStream str2) {
  // Scope variables
  const size_t result_size = MAX(str1.size, str2.size);
  unsigned int count = 0;

  // Buffers
  byte result_buffer[result_size];

  // Initialization
  memset(result_buffer, 0x0, result_size);

  // Algorithm: XOR + Count the number of 1s of result
  xor(str1, str2,
    &(ByteStream){ .size = result_size, .content = result_buffer }
  );

  for(int i=0; i < result_size; i++) {
    for(int j=0; j < BITS_IN__BYTE; j++) {
      count += (result_buffer[i] >> j) & 0x1;
    }
  }
  
  return count;
}
