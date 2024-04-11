#ifndef __UTILS__
#define __UTILS__

#define BYTE_NIBBLES 2

typedef unsigned char byte;
typedef struct SMessage {
  int status;
  char * content;
} Message;

const byte convertHexChars2Byte(char, char);
const byte hex_char2num(char);
const char hex_num2char(byte);


#endif