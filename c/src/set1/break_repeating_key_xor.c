#include "../../include/set1/break_repeating_key_xor.h"


int hamming_distance(const char * str1, const char * str2) {
  // Scope variables
  const size_t str1_size = strlen(str1);  
  const size_t str2_size = strlen(str2);
  const size_t result_size = MAX(str1_size, str2_size);
  unsigned int count = 0;

  // Buffers
  byte result_buffer[result_size];
  byte str1_buffer[str1_size];
  byte str2_buffer[str2_size];

  // Initialization  
  ByteData str1_bytes = {
    .size = str1_size,
    .content = str1_buffer
  };
  strncpy(str1_bytes.content, str1, str1_size);

  ByteData str2_bytes = {
    .size = str2_size,
    .content = str2_buffer
  };
  strncpy(str2_bytes.content, str2, str2_size);

  memset(result_buffer, 0x0, result_size);

  // Algorithm
  xor(
    (ByteData){ .size = str1_size, .content = str1_buffer },
    (ByteData){ .size = str2_size, .content = str2_buffer },
    &(ByteData){ .size = result_size, .content = result_buffer }
  );

  for(int i=0; i < result_size; i++) {
    for(int j=0; j < BIT_BYTE; j++) {
      count += (result_buffer[i] >> j) & 0x1;
    }
  }
  
  return count;
}


int guess_xor_keysize(const ByteData * ByteData) {
  // The base64-encoded message is compose by 30-character length rows,
  // separated by a newline character
  return 0;  
}