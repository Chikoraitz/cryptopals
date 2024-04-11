#include "../../include/set1/utils.h"

/*
  Receives two characters and outputs their hex conversion
  msd - Most Significant Digit
  lsd - Least Significant Digit
*/
const byte convertHexChars2Byte(char msd_char, char lsd_char) {
  byte msd, lsd;
  
  msd = hex_char2num(msd_char);
  lsd = hex_char2num(lsd_char);

  return (msd << 4) | lsd; 
}

const byte hex_char2num(char ch) {
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


const char hex_num2char(byte b) {
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
