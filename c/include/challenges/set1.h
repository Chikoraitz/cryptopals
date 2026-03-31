#ifndef __SET1_CHALLENGES__
#define __SET1_CHALLENGES__

#include "../../include/utils/data_conversion.h"
#include "../../include/utils/base64.h"
#include "../../include/crypto/xor.h"
#include "../../include/analysis/en_score.h"
#include "../../include/crypto/aes.h"

#define FILE_LINE_B64_BUFFER_SIZE 62


void c1(const char *, char *);
void c2(const char *, const char *, char *);
void c3(const char *, char *);
void c4(const char *, char *);
void c5(const char *, const char *, char *);
void c6(const char *, char *);
aes_status_code_t c7(const char *, char *, byte[AES_BLOCK_SIZE]);

void get_cipher_from_b64_str(const char *, ByteStream *);

#endif