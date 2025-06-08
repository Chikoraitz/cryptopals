#include "../../include/utils/base64.h"


const char base64_lookup_chars[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
const char base64_padding = '=';


/**
 * base64_convert() - Appends the base64-encoded block to the complete encoded string
 * @base64_res:   Keeps track of the complete base64-encoded string  
 * @b_block:      Byte buffer block of binary data subject to encoding
 * @b64_block:    String buffer block of the associated base64-encoded data
 * 
 * This function keeps track of the complete base64-encoded string by appending
 * the new block into the complete string at each block iteration. 
 * 
 * Return:
 * @pos:          Keeps track of index position of the complete base64-encoded string
*/
int base64_convert(char * base64_res, byte * b_block, char * b64_block, int pos) { 
  base64_block_encode(b64_block, b_block);
  for(int j=0; j < BASE64_BLOCK_BUFFER_SIZE; j++) {
    base64_res[pos] = b64_block[j];
    pos++;
  }

  return pos;
} 


/**
 * base64_block_encode() - Applies the rules of the base64 encoding scheme.
 * @encoded_block:  Base64 encoded output block of size 4 
 * @block_buffer:   Raw binary data input block of size 3
 * 
 * Base64 encoding scheme is defined in RFC 4648. 
 * The particular set of 64 characters chosen to represent the values are 
 * predefined in the base64_lookup_chars character array and the padding 
 * character is defined to be '='.
*/
void base64_block_encode(char * encoded_block, const byte * b_block) {
  byte data[BASE64_BLOCK_BUFFER_SIZE];

  for(int i=0; i < BASE64_BLOCK_BUFFER_SIZE; i++) {
    switch(i) {
      case 0: data[i] = b_block[0] >> 2; break;
      case 1: { 
        data[i] = b_block[1] >> 4 | (b_block[0] & ((byte)~0 >> 6)) << 4; 
      } break;
      case 2: { 
        data[i] = b_block[1] != 0 ? 
                  b_block[2] >> 6 | (b_block[1] & ((byte)~0 >> 4)) << 2 : 
                  (byte) ~0; 
      } break;
      case 3: { 
        data[i] = b_block[2] != 0 ? 
                  b_block[2] & ((byte) ~0 >> 2) : 
                  (byte)~0;
      }
    }
    
    encoded_block[i] = data[i] == (byte) ~0 ? '=' : base64_lookup_chars[data[i]];
  }
}
