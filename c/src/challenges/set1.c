#include "../../include/challenges/set1.h"

void c1(const char * hexstr_in, char * b64_result) {
  size_t buffer_size = strlen(hexstr_in) / NIBBLE_BYTE;
  byte buffer[buffer_size];
  ByteStream bs = BYTESTREAM(buffer, buffer_size);

  hexstr_to_bytes(hexstr_in, &bs);
  bytes_to_base64(bs, b64_result);
}


void c2(const char * xor_hexstr1, const char * xor_hexstr2, char * hexstr_result) {
  enum { BYTE_OPERAND_SIZE = 18 };
  
  byte xor_bytes_op1[BYTE_OPERAND_SIZE] = {0x0};
  byte xor_bytes_op2[BYTE_OPERAND_SIZE] = {0x0};
  byte xor_bytes_result[BYTE_OPERAND_SIZE] = {0x0};

  ByteStream xor_op1 = BYTESTREAM(xor_bytes_op1, BYTE_OPERAND_SIZE);
  ByteStream xor_op2 = BYTESTREAM(xor_bytes_op2, BYTE_OPERAND_SIZE);
  ByteStream xor_result = BYTESTREAM(xor_bytes_result, BYTE_OPERAND_SIZE);

  hexstr_to_bytes(xor_hexstr1, &xor_op1);
  hexstr_to_bytes(xor_hexstr2, &xor_op2);
  xor(xor_op1, xor_op2, &xor_result);
  bytes_to_hexstr(xor_result, hexstr_result);
}


void c3(const char * cipher_hexstr, char * msg) {
  enum { MSG_BUFFER_SIZE = 200 };

  size_t cipher_size = strlen(cipher_hexstr) / NIBBLE_BYTE;
  byte cipher_bytes_buffer[cipher_size], plaintext_bytes_buffer[cipher_size];
  byte key_buffer[1] = {0x0};
  ByteStream cipher_stream = BYTESTREAM(cipher_bytes_buffer, cipher_size);
  LanguageScore best = LANGUAGE_SCORE(plaintext_bytes_buffer, cipher_size, key_buffer, 1);

  //*best.key->content: 0x58
  hexstr_to_bytes(cipher_hexstr, &cipher_stream);
  single_xor_decrypt(cipher_stream, &best, 0.3);

  memcpy(msg, plaintext_bytes_buffer, cipher_size);
  msg[cipher_size] = 0;
}


void c4(const char * filepath, char * cipher_hexstr) {
  enum { CIPHER_SIZE = 30}; // All ciphers have size 30 bytes, so their hex string representation will have 60
  const size_t HEXSTR_BUFFER_SIZE = (CIPHER_SIZE * NIBBLE_BYTE) + 1;

  // Buffers
  char fstr[HEXSTR_BUFFER_SIZE];
  char cipher_plaintext_buffer[CIPHER_SIZE];
  char file_plaintext_buffer[CIPHER_SIZE];
  
  byte cipher_bytes_buffer[CIPHER_SIZE] = {0x0};  // Best score text for particular key of a cipher    
  byte file_bytes[CIPHER_SIZE] = {0x0};           // Best score text for particular cipher in file
  byte cipher_key_buffer[1] = {0x0}, file_key_buffer[1] = {0x0};

  FILE * fp; 
  ByteStream cipher_stream = BYTESTREAM(cipher_bytes_buffer, CIPHER_SIZE);
  LanguageScore cipher_best = LANGUAGE_SCORE(cipher_plaintext_buffer, CIPHER_SIZE, cipher_key_buffer, 1);
  LanguageScore file_best = LANGUAGE_SCORE(file_plaintext_buffer, CIPHER_SIZE, file_key_buffer, 1);

  // Algorithm
  if((fp = fopen(filepath, "r")) == NULL) {
    printf("Can't open file: %s\n", filepath);
  }
  else {
    while(fgets(fstr, HEXSTR_BUFFER_SIZE, fp) != NULL) {
      // Replace new line characters with string-terminal characters
      fstr[strcspn(fstr, "\n")] = '\0';
      hexstr_to_bytes(fstr, &cipher_stream);
      
      cipher_best.score = 1000.0;
      single_xor_decrypt(cipher_stream, &cipher_best, 0.3);
      
      if(cipher_best.score < file_best.score) {
        file_best.score = cipher_best.score;
        strncpy(file_best.decrypted->content, cipher_best.decrypted->content, CIPHER_SIZE);
        file_best.decrypted->content[CIPHER_SIZE] = '\0';
        *file_best.key->content = *cipher_best.key->content;
        strncpy(cipher_hexstr, fstr, HEXSTR_BUFFER_SIZE);
      }
    }
  }
  
  // file_best.decrypted->content: "Now that the party is jumping\n
  fclose(fp);
}


void c5(const char * plaintext, const char * key, char * cipher_hexstr) {
  enum { BUFFER_SIZE = 100 };
  const uint8_t key_size = strlen(key);
  const size_t plaintext_size = strlen(plaintext);
  
  // Buffer
  byte plaintext_buffer[BUFFER_SIZE] = {0x0};
  byte key_buffer[BUFFER_SIZE] = {0x0};
  byte cipher_bytes_buffer[plaintext_size];
  ByteStream text_stream = BYTESTREAM(cipher_bytes_buffer, plaintext_size);

  // Algorithm  
  strncpy(plaintext_buffer, plaintext, plaintext_size);
  strncpy(key_buffer, key, key_size);

  xor(
    (ByteStream){ .size = plaintext_size, .content = plaintext_buffer },
    (ByteStream){ .size = key_size, .content = key_buffer },
    &text_stream
  );

  bytes_to_hexstr(text_stream, cipher_hexstr);
}


void c6(const char * filename, char * key_buffer) {
  enum { 
    BINARY_BUFFER_SIZE = 3000,
    KEYSIZE_LOWER_BOUND = 2,
    KEYSIZE_UPPER_BOUND = 40,
  };

  // Fetch cipher
  byte cipher_buffer[BINARY_BUFFER_SIZE] = {0x0};
  ByteStream cipher = {
    .size = 0,
    .content = cipher_buffer
  };
  get_cipher_from_b64_str(filename, &cipher);
  
  // Algorithm
  int keysize, transpose_columns;
  byte transpose_block_buffer[100], transpose_buffer[100], key_char_buffer[1];
  ByteStream transposed_cipher = {
    .content = transpose_buffer
  };
  LanguageScore best;

  keysize = guess_xor_keysize(cipher, KEYSIZE_LOWER_BOUND, KEYSIZE_UPPER_BOUND, 0);
  const byte key[] = "Terminator X: Bring the noise";

  for(int i=0; i<keysize; i++) {
    transpose_vigenere_cipher(cipher, &transposed_cipher, keysize, i);    
    best.score = 300.0; // Arbitrarily large value
    best.decrypted = &(ByteStream){ .size = transposed_cipher.size, .content = transpose_block_buffer };
    best.key = &(ByteStream){ .size = 1, .content = key_char_buffer};

    single_xor_decrypt(transposed_cipher, &best, 0.4);
    key_buffer[i] = *(best.key->content);
  }
  
  key_buffer[keysize] = '\0';
}


aes_status_code_t c7(const char * filename, char * plaintext_buffer, byte key[AES_BLOCK_SIZE]) { 
  enum { BINARY_BUFFER_SIZE = 3000 };

  // Fetch cipher
  byte cipher_buffer[BINARY_BUFFER_SIZE] = {0x0};
  ByteStream cipher = {
    .size = 0,
    .content = cipher_buffer
  };
  get_cipher_from_b64_str(filename, &cipher);

  // Algorithm
  ByteStream plaintext;
  plaintext.content = plaintext_buffer;
  plaintext.size = cipher.size;

  aes_ctx_t aes_ctx = AES128_DEFAULT;
  aes_ctx.mode = ECB;
  aes_ctx.key = key;
  
  return aes_decrypt(aes_ctx, cipher, &plaintext);
}


void get_cipher_from_b64_str(const char * filename, ByteStream * cipher) {
  FILE * fp;
  char fstr[FILE_LINE_B64_BUFFER_SIZE] = "";
  byte file_bytes_buffer[(FILE_LINE_B64_BUFFER_SIZE / BASE64_BLOCK_SIZE) * BINARY_BLOCK_SIZE] = {0x0};  
  ByteStream file_block_bytes = {
    .content = file_bytes_buffer
  };

  // Open file, decode b64 string, and store the result
  if((fp = fopen(filename, "r")) == NULL) {
    printf("Can't open file: %s\n", filename);
  }
  else {
    while(fgets(fstr, FILE_LINE_B64_BUFFER_SIZE, fp) != NULL) {
      fstr[strcspn(fstr, "\n")] = 0; // Remove newlines
      base64_to_bytes(fstr, &file_block_bytes);
      file_block_bytes.size = get_bytes_size_from_base64str(fstr);
      memcpy(cipher->content + cipher->size, file_block_bytes.content, file_block_bytes.size);
      cipher->size += file_block_bytes.size;
    }
  }

  fclose(fp);
}