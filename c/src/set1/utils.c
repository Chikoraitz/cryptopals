#include "../../include/set1/utils.h"

/*
  Receives two characters and outputs their hex conversion
  msd - Most Significant Digit
  lsd - Least Significant Digit
*/
byte convertHexChars2Byte(char msd_char, char lsd_char) {
  byte msd, lsd;
  
  msd = char2hex(msd_char);
  lsd = char2hex(lsd_char);

  return (msd << 4) | lsd; 
}

byte char2hex(char ch) {
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
