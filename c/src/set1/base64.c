#include "../../include/set1/base64.h"

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
 * base64_encode_hex_string() - Converts string of hex binary data into its base64-encoding scheme.
 * @base64_res:   String output of the base64 encoding
 * @hex_string:   Hexadecimal data string
 * 
 * Function wrapper for the base64 encoding operation over raw data.
*/
void base64_encode_hex_string(char * base64_res, const char * hex_string) {
  Data * _d = allocate_bytes(strlen(hex_string) / NIBBLE_BYTE);

  import_raw_bytes(_d->payload, hex_string);
  base64_encode_raw(base64_res, _d);

  deallocate(_d);
}


/**
 * base64_decode_to_hex_string() - Converts base64-encoded scheme into its plain (hex) string data.
 * @hex_string:       Hexadecimal data string output
 * @base64_string:    Base64-encoded string
 * 
 * Function wrapper for the base64 decoding operation over raw data.
*/
void base64_decode_to_hex_string(char * hex_string, const char * base64_string) {

}


/**
 * base64_encode_raw() - Converts raw binary data into its base64 encoding scheme.
 * @base64_res:   String output of the base64 encoding
 * @raw_data:     Raw binary data
 * 
 * This function iterates over all raw binary data elements, aggregates them
 * in blocks of 3 and extrapolates the data into a block for 4 elements according
 * to the base46 encoding rules. 
*/
void base64_encode_raw(char * base64_res, const Data * data) {

  byte b_block[BINARY_BLOCK_BUFFER_SIZE];
  char b64_block[BASE64_BLOCK_BUFFER_SIZE];

  int b_block_i; 
  int pos = 0;

  for(int i=0; i < data->size; i++) {
    b_block_i = i % BINARY_BLOCK_BUFFER_SIZE;
    b_block[b_block_i] = data->payload[i];

    // Encode to base64 characters when binary buffer block is full
    if(b_block_i == BINARY_BLOCK_BUFFER_SIZE - 1) { 
      pos = base64_convert(base64_res, b_block, b64_block, pos);
    }
  }

  // If base64 block is not completed, fill the remaining bytes of the block with 0s 
  if(b_block_i < BINARY_BLOCK_BUFFER_SIZE - 1) {
    for(int i=b_block_i+1; i < BINARY_BLOCK_BUFFER_SIZE; i++) b_block[i] = 0x0;
    pos = base64_convert(base64_res, b_block, b64_block, pos);
  }

  base64_res[pos] = '\0';
} 


/**
 * base64_decode_raw() - Converts raw binary data into its base64 encoding scheme.
 * @base64_res:   String output of the base64 encoding
 * @raw_data:     Raw binary data
 * 
 * This function iterates over all raw binary data elements, aggregates them
 * in blocks of 3 and extrapolates the data into a block for 4 elements according
 * to the base46 encoding rules. 
*/
void base64_decode_raw(Data * hex_data, const char * base64_string) {

}
