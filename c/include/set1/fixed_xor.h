#ifndef __FIXEDXOR_HEADER__
#define __FIXEDXOR_HEADER__

#include <stdint.h>

#include "utils.h"

typedef struct SRawData{
  byte * data;
  int size;
} raw_data;

void xor(SymEncryptMessage *, raw_data, raw_data);

#endif