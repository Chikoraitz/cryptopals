#include "../../include/set1/base64.h"

const char base64_lookup_chars[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
const char base64_padding = '=';


/**
 * get_base64_size() - Calculates the base64-encoded string size
 * @hex_string: Hexadecimal string representation of raw binary data 
 * 
 * This function calculates the size of the associated base64-encoded string.
 * Since we know that base64-encoded strings introduce an overhead of 33% on 
 * the message, all the parameters are known to calculate the string size of 
 * the associated base64-encoded string.
 * 
 * Return: 
 * @(int): Base64-encoded string size 
*/
const int get_base64_size(const char * hex_string) {
  const int n_bytes = strlen(hex_string) / NIBBLE_BYTE;
  return ((BASE64_BLOCK_BUFFER_SIZE * n_bytes / BINARY_BLOCK_BUFFER_SIZE) + 3) & ~3;
}


/**
 * base64_from_hex_string() - Converts string of hex binary data into its base64 encoding scheme.
 * @res:          String output of the base64 encoding
 * @hex_string:   Hexadecimal data string
 * 
 * This function first converts the hex string of data into its raw format, 
 * before proceeding with its base64 encoding.
*/
void base64_from_hex_string(char * res, const char * hex_string) {
  Data raw_data;
  raw_data.size = strlen(hex_string) / NIBBLE_BYTE;
  raw_data.content = (byte *) malloc(sizeof(byte) * raw_data.size);

  import_raw_bytes(raw_data.content, hex_string);
  base64_from_raw(res, raw_data);

  free(raw_data.content);
}


/**
 * base64_from_raw() - Converts raw binary data into its base64 encoding scheme.
 * @res:        String output of the base64 encoding
 * @raw_data:   Raw binary data
 * 
 * This function iterates over all raw binary data elements, aggregates them
 * in blocks of 3 and extrapolates the data into a block for 4 elements according
 * to the base46 encoding rules. 
*/
void base64_from_raw(char * res, const Data raw_data) {

  byte b_block[BINARY_BLOCK_BUFFER_SIZE];
  char b64_block[BASE64_BLOCK_BUFFER_SIZE];

  int b_block_i; 
  int pos = 0;

  for(int i=0; i < raw_data.size; i++) {
    b_block_i = i % BINARY_BLOCK_BUFFER_SIZE;
    b_block[b_block_i] = raw_data.content[i];

    // Encode to base64 characters when binary buffer block is full
    if(b_block_i == BINARY_BLOCK_BUFFER_SIZE - 1) { 
      pos = convert(res, b_block, b64_block, pos);
    }
  }

  // If base64 block is not completed, fill the remaining bytes of the block with 0s 
  if(b_block_i < BINARY_BLOCK_BUFFER_SIZE - 1) {
    for(int i=b_block_i+1; i < BINARY_BLOCK_BUFFER_SIZE; i++) b_block[i] = 0x0;
    pos = convert(res, b_block, b64_block, pos);
  }

  res[pos] = '\0';
} 


/**
 * convert() - Appends the base64-encoded block to the complete encoded string
 * @b64_res:      Keeps track of the complete base64-encoded string  
 * @b_block:      Byte buffer block of binary data subject to encoding
 * @b64_block:    String buffer block of the associated base64-encoded data
 * 
 * This function keeps track of the complete base64-encoded string by appending
 * the new block into the complete string at each block iteration. 
 * 
 * Return:
 * @pos:          Keeps track of index position of the complete base64-encoded string
*/
static int convert(char * b64_res, byte * b_block, char * b64_block, int pos) { 
  block_encode(b64_block, b_block);
  for(int j=0; j < BASE64_BLOCK_BUFFER_SIZE; j++) {
    b64_res[pos] = b64_block[j];
    pos++;
  }

  return pos;
} 


/**
 * block_encode() - Applies the rules of the base64 encoding scheme.
 * @encoded_block:  Base64 encoded output block of size 4 
 * @block_buffer:   Raw binary data input block of size 3
 * 
 * Base64 encoding scheme is defined in RFC 4648. 
 * The particular set of 64 characters chosen to represent the values are 
 * predefined in the base64_lookup_chars character array and the padding 
 * character is defined to be '='.
*/
static void block_encode(char * encoded_block, const byte * b_block) {
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
