#include "../../include/utils/data_conversion.h"


static inline const byte hex_char2value(char ch) {
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


static inline const char hex_value2char(byte b) {
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


void hexstr_to_bytes(const char in[], byte out[]) {
  int out_i = 0;

  for(int i=0; i<strlen(in); i++) {    
    // Most significant nibble
    if(i % NIBBLE_BYTE == MSN) {
      out[out_i] = (hex_char2value(in[i]) & 0xf);
      out[out_i] <<= BIT_NIBBLE; 
    }
    // Least significant nibble
    else {
      out[out_i] |= (hex_char2value(in[i]) & 0xf);
      out_i++;
    }
  }

  for(int i=out_i; i<strlen(out); i++) out[out_i] = 0x0;
}


void bytes_to_hexstr(const byte * in, char * out, const size_t in_size) {
  int in_i = 0;
  const size_t out_size = in_size * NIBBLE_BYTE;

  for(int i=0; i<out_size; i++) {
    // Most significant nibble
    if(i % NIBBLE_BYTE == MSN) {
      out[i] = hex_value2char(in[in_i] >> BIT_NIBBLE);
    }
    // Least significant nibble
    else {
      out[i] = hex_value2char(in[in_i] & 0xf);
      in_i++;
    }
  }

  out[out_size] = '\0'; // Just in case
}