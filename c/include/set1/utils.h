#ifndef __UTILS__
#define __UTILS__

#include <string.h>
#include <stdio.h>

#define BYTE_NIBBLES  2
#define BIT_NIBBLES   4

typedef unsigned char byte;
typedef enum { MSN = 0, LSN = 1 } nibble;
typedef enum {Error = -1, Plaintext = 0, Encrypted = 1} code;

typedef struct SSymEncryptMessage {
  code status;
  char * status_msg;
  char * algorithm;
  char * data;
} SymEncryptMessage;

const byte convertHexChars2Byte(char, char);
const byte hex_char2value(char);
const char hex_value2char(byte);

void import_raw_bytes(byte *, const char *);
void export_raw_bytes(char *, const byte *, const int);

#endif