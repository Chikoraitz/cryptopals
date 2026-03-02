#include "../../include/set1/fixed_xor.h"


void xor_legacy(Data * msg, const Data * op1, const Data * op2) {
  const int cipher_size = (op1->size > op2->size) ? op1->size : op2->size; 

  for(int i = 0; i < cipher_size; i++) {
    msg->payload[i] = op1->payload[i % op1->size] ^ op2->payload[i % op2->size];
  }
}


void xor(const byte * in_op1, const byte * in_op2, byte * out, const size_t size) {
  for(int i=0; i<size; i++) {
    out[i] = in_op1[i] ^ in_op2[i];
  }
}