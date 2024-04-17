#include "../../include/set1/utils.h"

/**
 * Receives two characters and outputs their hex conversion
 * msd - Most Significant Digit
 * lsd - Least Significant Digit
*/
const byte convertHexChars2Byte(char msd_char, char lsd_char) {
  byte msd, lsd;
  
  msd = hex_char2value(msd_char);
  lsd = hex_char2value(lsd_char);

  return (msd << 4) | lsd; 
}


/**
 * Converts the character representation of an hexadecimal
 * number to its binary value 
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
 * Converts the binary value of an hexadecimal
 * number to its character representation 
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
 * Convert a string into an array of its associated bytes values. 
 * Stores the result into the provided structure.
 * Receives as arguments:  
 *  - Memory location of the byte array output
 *  - String of the binary data in its hexadecimal representation  
*/
void import_raw_bytes(byte out_ptr[], const char in[]) {
  int out_i = 0;

  for(int i = 0; i < strlen(in); i++) {
    // Most significant nibble
    if(i % BYTE_NIBBLES == MSN) {
      out_ptr[out_i] = (hex_char2value(in[i]) & 0xf);
      out_ptr[out_i] <<= BIT_NIBBLES; 
    }
    // Least significant nibble
    else {
      out_ptr[out_i] |= (hex_char2value(in[i]) & 0xf);
      out_i++;
    }
  }
}


/**
 * Convert an array of bytes values into its associated hex characters.
 * Stores the result into the provided structure.
 * Receives as arguments:
 * - Memory location of the string output
 * - Raw binary data  
*/
void export_raw_bytes(char out_ptr[], const byte in[], const int buffer_size) {
  int in_i = 0;
  int string_size = buffer_size * BYTE_NIBBLES;

  for(int i = 0; i < string_size; i++) {
    // Most significant nibble
    if(i % BYTE_NIBBLES == MSN) {
      out_ptr[i] = hex_value2char(in[in_i] >> BIT_NIBBLES);
    }
    // Least significant nibble
    else {
      out_ptr[i] = hex_value2char(in[in_i] & 0xf);
      in_i++;
    }
  }

  out_ptr[string_size] = '\0';
}