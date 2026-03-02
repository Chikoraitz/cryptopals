#include "../../include/set1/break_repeating_key_xor.h"

/**
 * hamming_distance() - Calculates the bit Hamming distance between two strings
 * @string1:  Comparison operand
 * @string2:  Comparison operand
 * @s_len:    String length
 * 
 * Hamming distance is the number of differing bits of two strings.
 * Since the only allowed operation is substitution, the Hammming distance
 * assumes that the strings are of equal length.
 * The differing bits can be calculated by counting the number of 1s of 
 * their XOR product (inequality operation). 
 * 
 * Return:
 * @(int): Hamming distance
*/
static int hamming_distance(const char * string1, const char * string2, const int s_len) {
  // ByteData * byte_stream1 = allocate_bytes(s_len);
  // ByteData * byte_stream2 = allocate_bytes(s_len);
  // ByteData * byte_res = allocate_bytes(s_len);

  // int count = 0;

  // strncpy(byte_stream1->content, string1, s_len);
  // strncpy(byte_stream2->content, string2, s_len);

  // xor(byte_res, byte_stream1, byte_stream2);

  // for(int i=0; i < byte_res->size; i++) {
  //   for(int j=0; j < BIT_BYTE; j++) {
  //     count += (byte_res->content[i] >> j) & 0x1;
  //   }
  // }

  // deallocate(byte_stream1);
  // deallocate(byte_stream2);
  // deallocate(byte_res);
  
  // return count;
  return 0;
}


int guess_xor_keysize(const ByteData * ByteData) {
  // The base64-encoded message is compose by 30-character length rows,
  // separated by a newline character
  char buffer[30];
  
}