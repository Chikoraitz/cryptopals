#include "../../include/set1/fixed_xor.h"

void xor(const ByteStream in_op1, const ByteStream in_op2, ByteStream * out) {
  for(int i=0; i<out->size; i++) {
    out->content[i] = in_op1.content[i % in_op1.size] ^ in_op2.content[i % in_op2.size];
  }
}