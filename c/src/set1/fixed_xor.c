#include <string.h>

#include "../../include/set1/fixed_xor.h"

#include <stdio.h>
#include <stdlib.h>

/*
 * Receives two equal-sized buffers and performs XOR operation
 * over the content of the two buffers. 
 * The function expects two strings and returns a string.
*/
Message xor(byte buffer1[], byte buffer2[]) {
  Message m = { .status = -1 };

  // Check if buffers are of equal length
  if(strlen(buffer1) != strlen(buffer2)){
    m.content = "Buffers are not of equal size!";
    return m;
  }

  size_t buffer_size = strlen(buffer1) + 1;
  m.content = (char *) malloc(buffer_size);
  byte res, operand1, operand2;

  for(int i = 0; i < buffer_size; i++) {
    // Convert buffers to byte representation
    operand1 = hex_char2num(buffer1[i]);
    operand2 = hex_char2num(buffer2[i]);

    // Performs XOR operation
    res = operand1 ^ operand2;

    // Converts the values back to hex string representation
    m.content[i] = hex_num2char(res);
  }

  m.content[buffer_size - 1] = '\0';
  m.status = 0;
  return m;
}