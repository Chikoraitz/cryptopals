#include "../../include/set1/fixed_xor.h"

/*
 * xor() - Performs XOR operation
 * @msg:  Memory address of the XOR result
 * @op1:  XOR operand
 * @op2:  XOR operand
 * 
 * Iterates over all byte elements of each operand arguments and 
 * performs their XOR operation. The XOR result content will have 
 * the size of the largest operand supplied, and cyclically repeats 
 * the smaller operand throughout the operation.
*/
void xor(Data * msg, const Data op1, const Data op2) {
  const int cipher_size = (op1.size > op2.size) ? op1.size : op2.size; 

  for(int i = 0; i < cipher_size; i++) {
    msg->content[i] = op1.content[i % op1.size] ^ op2.content[i % op2.size];
  }
}