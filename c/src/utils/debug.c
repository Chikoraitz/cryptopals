#include "../../include/utils/debug.h"

void debug_buffer_content(const char * prefix, byte buffer[], size_t buff_size) {
  printf("%s", prefix);
  for(int i=0; i < buff_size; i++) printf("0x%2x ", buffer[i]);
  printf("\n");
}