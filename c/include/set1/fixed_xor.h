#ifndef __FIXED_XOR_HEADER__
#define __FIXED_XOR_HEADER__

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../utils/data_conversion.h"

#define MAX(x, y) (((x) > (y)) ? (x) : (y))

void xor(const ByteData, const ByteData, ByteData *); 

#endif