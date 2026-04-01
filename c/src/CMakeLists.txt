#[[ Library Functions ]]

list(APPEND HEADER_FILES 
      "${CMAKE_SOURCE_DIR}/include/utils/base64.h"
      "${CMAKE_SOURCE_DIR}/include/utils/data_conversion.h"
      "${CMAKE_SOURCE_DIR}/include/utils/debug.h"
      "${CMAKE_SOURCE_DIR}/include/crypto/aes.h"
      "${CMAKE_SOURCE_DIR}/include/crypto/xor.h"
      "${CMAKE_SOURCE_DIR}/include/crypto/hash.h"
      "${CMAKE_SOURCE_DIR}/include/analysis/en_score.h"
      "${CMAKE_SOURCE_DIR}/include/analysis/hamming.h"
      "${CMAKE_SOURCE_DIR}/include/analysis/aes.h")

list(APPEND SRC_FILES 
      "${CMAKE_CURRENT_SOURCE_DIR}/utils/base64.c"
      "${CMAKE_CURRENT_SOURCE_DIR}/utils/data_conversion.c"
      "${CMAKE_CURRENT_SOURCE_DIR}/utils/debug.c"
      "${CMAKE_CURRENT_SOURCE_DIR}/crypto/aes.c"
      "${CMAKE_CURRENT_SOURCE_DIR}/crypto/xor.c"
      "${CMAKE_CURRENT_SOURCE_DIR}/crypto/hash.c"
      "${CMAKE_CURRENT_SOURCE_DIR}/analysis/en_score.c"
      "${CMAKE_CURRENT_SOURCE_DIR}/analysis/hamming.c"
      "${CMAKE_CURRENT_SOURCE_DIR}/analysis/aes.c")


#[[ Challenges ]]
list(APPEND HEADER_FILES 
      "${CMAKE_SOURCE_DIR}/include/challenges/set1.h")

list(APPEND SRC_FILES 
      "${CMAKE_CURRENT_SOURCE_DIR}/challenges/set1.c")


add_library(cryptopals_lib ${SRC_FILES} ${HEADER_FILES})
target_include_directories(cryptopals_lib PRIVATE "${CMAKE_SOURCE_DIR}/include/challenges")