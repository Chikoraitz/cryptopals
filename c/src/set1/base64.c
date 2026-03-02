#include "../../include/set1/base64.h"

const char base64_lookup_chars[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
const char base64_padding = '=';


const int get_base64_size(const char * hexstr) {
  const int n_bytes = strlen(hexstr) / NIBBLE_BYTE;
  return ((BASE64_BLOCK_SIZE * n_bytes / BINARY_BLOCK_SIZE) + 3) & ~3;
}


static inline int base64_encode_block(byte * in_b_block, char * in_b64_block, char * out_base64_block, int pos) { 
  byte data[BASE64_BLOCK_SIZE];

  for(int i=0; i < BASE64_BLOCK_SIZE; i++) {
    switch(i) {
      case 0: data[i] = in_b_block[0] >> 2; break;
      case 1: { 
        data[i] = in_b_block[1] >> 4 | (in_b_block[0] & ((byte)~0 >> 6)) << 4; 
      } break;
      case 2: { 
        data[i] = in_b_block[1] != 0 ? 
                  in_b_block[2] >> 6 | (in_b_block[1] & ((byte)~0 >> 4)) << 2 : 
                  (byte)~0; 
      } break;
      case 3: { 
        data[i] = in_b_block[2] != 0 ? 
                  in_b_block[2] & ((byte) ~0 >> 2) : 
                  (byte)~0;
      }
    }
    
    // Check for padding content, else lookup the encoding scheme
    out_base64_block[pos] = data[i] == (byte)~0 ? '=' : base64_lookup_chars[data[i]];
    pos++;
  }

  return pos;
}


void bytes_to_base64(const byte * data, char * result_buffer) {
  byte b_block[BINARY_BLOCK_SIZE];
  char b64_block[BASE64_BLOCK_SIZE];

  int b_block_i; 
  int pos = 0;

  for(int i=0; i < strlen(data); i++) {
    // Fill the binary buffer block (size 3)
    b_block_i = i % BINARY_BLOCK_SIZE;
    b_block[b_block_i] = data[i];

    // When filled, encode to base64 schema
    if(b_block_i == BINARY_BLOCK_SIZE - 1) {
      pos = base64_encode_block(b_block, b64_block, result_buffer, pos);
    }
  }

  /** Padding:
   *  If base64 block is not completed, 
  /*  fill the remaining bytes of the block with 0s 
  */
  if(b_block_i < BINARY_BLOCK_SIZE - 1) {
    for(int i=b_block_i+1; i < BINARY_BLOCK_SIZE; i++) b_block[i] = 0x0;
    pos = base64_encode_block(b_block, b64_block, result_buffer, pos);
  }

  result_buffer[pos] = '\0';
} 

