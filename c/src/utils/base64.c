#include "../../include/utils/base64.h"

const char base64_lookup_chars[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
const char base64_padding = '=';


const int get_base64_size_from_hexstr(const char * hexstr) {
  const int n_bytes = strlen(hexstr) / NIBBLE_BYTE;
  return ((BASE64_BLOCK_SIZE * n_bytes / BINARY_BLOCK_SIZE) + 3) & ~3;
}

const int get_bytes_size_from_base64str(const char * b64_str) {
  uint8_t n_padding = 0;
  int b64str_size = strlen(b64_str);
  
  for(int i=0; i<b64str_size; i++) {
    if(b64_str[i] == base64_padding) n_padding++;
  }

  // Workaround for round up
  return (((b64str_size + BASE64_BLOCK_SIZE - 1) / BASE64_BLOCK_SIZE) * BINARY_BLOCK_SIZE) - n_padding;
}


static inline int base64_encode_block(byte * in_b_block, char * in_b64_block, char * out_base64_block, int pos) { 
  byte data[BASE64_BLOCK_SIZE];

  for(int i=0; i < BASE64_BLOCK_SIZE; i++) {
    switch(i) {
      case 0: data[i] = in_b_block[0] >> 2; break;
      case 1: { 
        data[i] = in_b_block[1] >> 4 | (in_b_block[0] & 0x03) << 4; 
      } break;
      case 2: { 
        data[i] = in_b_block[1] != 0 ? 
                  in_b_block[2] >> 6 | (in_b_block[1] & 0x0f) << 2 :
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


static inline int base64_decode_block(char * in_b64_block, byte * out, int pos) {
  byte b64_block[BASE64_BLOCK_SIZE];
  uint8_t lookup_index;

  // Reverse lookup to find index
  for(int i=0; i<BASE64_BLOCK_SIZE; i++) {
    lookup_index = 0;
    while(in_b64_block[i] != base64_lookup_chars[lookup_index]) lookup_index++;
    b64_block[i] = lookup_index;
  }

  for(int i=0; i<BINARY_BLOCK_SIZE; i++) {
    switch(i) {
      case 0: 
        out[pos] = b64_block[i] << 2 | b64_block[i+1] >> 4;
        break;
      case 1: 
        out[pos] = b64_block[i] << 4 | (b64_block[i+1] & 0x3C) >> 2; // Mask: 0011 1100
        break; 
      case 2: out[pos] = b64_block[i] << 6 | b64_block[i+1];
    }

    pos++;
  }

  return pos;
}


void bytes_to_base64(const ByteStream in, char * result_buffer) {
  byte b_block[BINARY_BLOCK_SIZE];
  char b64_block[BASE64_BLOCK_SIZE];

  int b_block_i; 
  int pos = 0;

  for(int i=0; i<in.size; i++) {
    // Fill the binary buffer block (size 3)
    b_block_i = i % BINARY_BLOCK_SIZE;
    b_block[b_block_i] = in.content[i];

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


void base64_to_bytes(const char * in, ByteStream * out) {
  char b64_block[BASE64_BLOCK_SIZE];
  int b64_block_i;
  int pos = 0;

  out->size = get_bytes_size_from_base64str(in);

  for(int i=0; i<strlen(in); i++) {
    // Fill the base64 buffer block (size 4)
    b64_block_i = i % BASE64_BLOCK_SIZE;
    b64_block[b64_block_i] = in[i];

    // When filled, decode base64 string to its byte format
    if(b64_block_i == BASE64_BLOCK_SIZE - 1) {
      pos = base64_decode_block(b64_block, out->content, pos);
    }
  }

  out->content[out->size] = '\0';
}