#[[ Set 1 Challenges ]]

file(GLOB HEADER_LIST CONFIGURE_DEPENDS "${set1_SOURCE_DIR}/include/set1/*.h")
add_library(base64_lib STATIC set1/base64.c ${HEADER_LIST})
target_include_directories(base64_lib PUBLIC "${set1_SOURCE_DIR}/include/set1")
