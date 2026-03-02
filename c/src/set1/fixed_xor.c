#include "../../include/set1/fixed_xor.h"

void xor(const ByteData in_op1, const ByteData in_op2, ByteData * out) {
  for(int i=0; i<out->size; i++) {
    out->content[i] = in_op1.content[i % in_op1.size] ^ in_op2.content[i % in_op2.size];
  }
}