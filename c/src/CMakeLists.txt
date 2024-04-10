#[[ Set 1 Challenges ]]

list(APPEND HEADER_FILES 
      "${CMAKE_SOURCE_DIR}/include/set1/utils.h"
      "${CMAKE_SOURCE_DIR}/include/set1/base64.h"
      "${CMAKE_SOURCE_DIR}/include/set1/fixed_xor.h")

list(APPEND SRC_FILES 
      "${CMAKE_CURRENT_SOURCE_DIR}/set1/utils.c"
      "${CMAKE_CURRENT_SOURCE_DIR}/set1/base64.c"
      "${CMAKE_CURRENT_SOURCE_DIR}/set1/fixed_xor.c")


#[[ Set 2 Challenges ]]
#[[ Set 3 Challenges ]]
#[[ Set 4 Challenges ]]
#[[ Set 5 Challenges ]]
#[[ Set 6 Challenges ]]
#[[ Set 7 Challenges ]]
#[[ Set 8 Challenges ]]


add_library(cryptopals_lib ${SRC_FILES} ${HEADER_FILES})
target_include_directories(cryptopals_lib PRIVATE "${CMAKE_SOURCE_DIR}/include/set1")