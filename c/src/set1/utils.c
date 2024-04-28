#include "../../include/set1/utils.h"

/**
 * hex_char2value() - Converts the hexadecimal character into its value
 * @ch: Finite set of 16 characters that make up the hexadecimal representation 
 *      of a byte nibble
 * 
 * Alphanumeric characters have different values from their ASCII representations.
 * This function associates the hexadecimal character representation to its intrinsic 
 * byte value. 
 * 
 * Return:
 * @(byte): A value between 0 and 15. 
*/
const byte hex_char2value(char ch) {
  switch(ch) {
    case '0':
    case '1':
    case '2':
    case '3':
    case '4':
    case '5':
    case '6':
    case '7':
    case '8':
    case '9': return ch - '0';
    case 'a': 
    case 'b':
    case 'c':
    case 'd':
    case 'e':
    case 'f': return ch - 'a' + 10;
    case 'A': 
    case 'B':
    case 'C':
    case 'D':
    case 'E':
    case 'F': return ch - 'A' + 10;
    default: return '\0';
  }
}


/**
 * hex_value2char() - Converts the value into its associated hexadecimal character
 * @b: A value betwwen 0 and 15.
 * 
 * Inverse conversion of hex_value2char(). 
 * Alphanumeric characters have different values from their ASCII representations.
 * This function associates its byte value to its hexadecimal character representation.
 * 
 * Return: 
 * @(char): An hexadecimal character. 
*/
const char hex_value2char(byte b) {
  switch(b) {
    case 0:   return '0';
    case 1:   return '1';
    case 2:   return '2';
    case 3:   return '3';
    case 4:   return '4';
    case 5:   return '5';
    case 6:   return '6';
    case 7:   return '7';
    case 8:   return '8';
    case 9:   return '9';
    case 10:  return 'a';
    case 11:  return 'b';
    case 12:  return 'c';
    case 13:  return 'd';
    case 14:  return 'e';
    case 15:  return 'f';
  } 
}


/**
 * import_raw_bytes() - Converts an hexadecimal string into its associated raw binary data array 
 * @out_ptr:  Output byte buffer
 * @in:       Input string
 * 
 * This function converts binary data in its hexadecimal string form,
 * into an array of bytes with its associated raw value. Since each character
 * represents a nibble, the resultant byte array will have half the size of 
 * the input.   
*/
void import_raw_bytes(byte out_ptr[], const char in[]) {
  int out_i = 0;

  for(int i = 0; i < strlen(in); i++) {
    // Most significant nibble
    if(i % NIBBLE_BYTE == MSN) {
      out_ptr[out_i] = (hex_char2value(in[i]) & 0xf);
      out_ptr[out_i] <<= BIT_NIBBLE; 
    }
    // Least significant nibble
    else {
      out_ptr[out_i] |= (hex_char2value(in[i]) & 0xf);
      out_i++;
    }
  }
}


/**
 * export_raw_bytes() - Converts a raw binary data array into its associated hexadecimal string
 * @out:  Output string
 * @in:   Input byte buffer
 * 
 * This function iterates over all elements of a raw byte buffer and converts
 * them into their associated pair of hexadecimal characters. The resultant string
 * will have twice the size of the byte array size.
*/
void export_raw_bytes(char * out, const Data in) {
  int in_i = 0;
  int string_size = in.size * NIBBLE_BYTE;

  for(int i = 0; i < string_size; i++) {
    // Most significant nibble
    if(i % NIBBLE_BYTE == MSN) {
      out[i] = hex_value2char(in.content[in_i] >> BIT_NIBBLE);
    }
    // Least significant nibble
    else {
      out[i] = hex_value2char(in.content[in_i] & 0xf);
      in_i++;
    }
  }

  out[string_size] = '\0';
}