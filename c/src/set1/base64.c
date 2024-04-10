#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../../include/set1/base64.h"

#define UPPER_BOUND 300

/*
  Receives the input string in hexadecimal format
  Outputs the associated base64 encoding of the hex input string
  For simplicity, it bounds the base64 encoded output to 300 characters  
*/
byte * hex2base64(char hex_string[]) { 
  static byte base64_encoded[UPPER_BOUND];

  byte base64_encoded_temp[UPPER_BOUND] = {'\0'};
  struct SEncodingIteration base64_iteration;
  int index = 0;

  base64_iteration.buffer[BLOCK_SIZE] = '\0';
  base64_iteration.interpolated_data[BLOCK_STRING_SIZE] = '\0';

  for(int pos=0; pos < strlen(hex_string); pos += BYTE_NIBBLES) {
    base64_iteration.buffer[index % BLOCK_SIZE] = convertHexChars2Byte(hex_string[pos], hex_string[pos+1]);

    // Buffer full or input last element
    if(index % BLOCK_SIZE == BLOCK_SIZE - 1 || pos == strlen(hex_string) - BYTE_NIBBLES) {

      // When reaching last element, fill the remaining buffer elements with null
      if(pos == (strlen(hex_string) - 2)) {
        for(int j = (index % BLOCK_SIZE) + 1; j < BLOCK_SIZE; j++) base64_iteration.buffer[j] = '\0';
      }

      memcpy(base64_iteration.interpolated_data, blockInterpolation(base64_iteration.buffer), BLOCK_STRING_SIZE);
      strncat(base64_encoded_temp, base64LookupBlockEncoding(base64_iteration.interpolated_data), BLOCK_STRING_SIZE);
    }

    index++;
  }

  memcpy(base64_encoded, base64_encoded_temp, UPPER_BOUND);
  
  return base64_encoded; 
}


/*
  Receives the 3-character buffer and outputs the associated encoded version
  The character output will be bounded between 0 and 63. If >= 64, then assumes
  that the input has ended and adds the padding character  
*/
byte * blockInterpolation(byte buffer[]) {
  static byte output[BLOCK_STRING_SIZE + 1];

  for(int i=0; i < BLOCK_STRING_SIZE; i++) {
    switch(i) {
      case 0: output[i] = buffer[0] >> 2; break;
      case 1: output[i] = buffer[1] >> 4 | (buffer[0] & ((byte)~0 >> 6)) << 4; break;
      case 2: output[i] = buffer[1] != 0 ? buffer[2] >> 6 | (buffer[1] & ((byte)~0 >> 4)) << 2 : (byte) ~0; break;
      case 3: output[i] = buffer[2] != 0 ? buffer[2] & ((byte) ~0 >> 2) : (byte)~0;
    }
  }

  return output;
}


byte * base64LookupBlockEncoding(byte interpolated_data[]) {
  static byte base64_encoded_block[BLOCK_STRING_SIZE];

  for(int i=0; i < BLOCK_STRING_SIZE; i++) {
    base64_encoded_block[i] = interpolated_data[i] == (byte) ~0 ? 
                                '=' :
                                base64_lookup_chars[interpolated_data[i]];
  }
  
  return base64_encoded_block;
}

