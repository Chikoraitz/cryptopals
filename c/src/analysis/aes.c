#include "../../include/analysis/aes.h"

boolean_t is_ecb_cipher(const ByteStream stream) {
  byte eval_block[AES_BLOCK_SIZE];
  byte block[AES_BLOCK_SIZE];
  
  for(int offset=0; offset < stream.size; offset += AES_BLOCK_SIZE) {
    memcpy(eval_block, stream.content + offset, AES_BLOCK_SIZE);
    for(int next=offset + AES_BLOCK_SIZE; next < stream.size; next += AES_BLOCK_SIZE) {
      memcpy(block, stream.content + next, AES_BLOCK_SIZE);
      if(memcmp(eval_block, block, AES_BLOCK_SIZE) == 0) return TRUE;
    }
  }

  return FALSE;
}