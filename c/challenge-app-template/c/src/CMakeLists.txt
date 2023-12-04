file(GLOB HEADER_LIST CONFIGURE_DEPENDS "${convertHex2Base64_SOURCE_DIR}/include/*.h")
add_library(base64_lib STATIC base64.c ${HEADER_LIST})
target_include_directories(base64_lib PUBLIC "${convertHex2Base64_SOURCE_DIR}/include")
