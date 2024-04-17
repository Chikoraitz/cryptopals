#include <string.h>

#include "../../include/set1/fixed_xor.h"

#include <stdio.h>
#include <stdlib.h>


/*
 * Receives two buffers and performs XOR operation over
 * the content of the two buffers.
 * The function expects two raw_data data structures and 
 * outputs the result into a SymEncryptMessage data type variable 
 * Both data structures are defined in utils.h
*/
void xor(SymEncryptMessage * msg, raw_data op1, raw_data op2) {
  msg->algorithm = "XOR";
  msg->status = Error;

  const int cipher_size = (op1.size > op2.size) ? op1.size : op2.size; 
  byte res[cipher_size];

  for(int i = 0; i < cipher_size; i++) {
    // Performs XOR operation over the operands
    res[i] = op1.data[i % op1.size] ^ op2.data[i % op2.size];
  }

  export_raw_bytes(msg->data, res, cipher_size);
  msg->status = Encrypted;
}