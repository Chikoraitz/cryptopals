#include "../../include/crypto/aes.h"

const char SBOX[] = {0x0};

// === Encryption functions ===

void aes_encrypt(AES_CONFIG config, enum mode mode) {
  switch(mode) {
    case ECB: ecb_encrypt(); break;
  }
}

void ecb_encrypt() {

}


// === Decryption functions ===

void aes_decrypt(AES_CONFIG config, const ByteStream ciphertext, ByteStream * plaintext, enum mode mode) {
  void (* decrypt)(ByteStream, ByteStream *);
  
  switch(mode) {
    case ECB: decrypt = &ecb_decrypt; break;
  }

  for(uint8_t round = 0; round < config.rounds; round++) {
    decrypt(ciphertext, plaintext);
  }
}


void ecb_decrypt(ByteStream ciphertext, ByteStream * plaintext) {
  printf("Hello\n");
}