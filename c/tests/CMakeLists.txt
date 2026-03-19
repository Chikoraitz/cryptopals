#[[ == Smoke Test == ]]

add_cmocka_test(smoke_test
                SOURCES smoke_test.c
                COMPILE_OPTIONS ${DEFAULT_C_COMPILE_FLAGS}
                LINK_LIBRARIES "${CMOCKA_LIBRARIES}")

add_cmocka_test_environment(smoke_test)


#[[ == Utility Tests == ]]

add_cmocka_test(utils_test
                SOURCES utils_test.c "${CMAKE_SOURCE_DIR}/include/utils"
                COMPILE_OPTIONS ${DEFAULT_C_COMPILE_FLAGS}
                LINK_LIBRARIES "${CMOCKA_LIBRARIES}" cryptopals_lib)

target_include_directories(utils_test PRIVATE "${CMOCKA_INCLUDE_DIRS}" "${CMAKE_SOURCE_DIR}/include/utils")
add_cmocka_test_environment(utils_test)


#[[ == Analysis Tests == ]]

add_cmocka_test(analysis_test
                SOURCES analysis_test.c "${CMAKE_SOURCE_DIR}/include/analysis"
                COMPILE_OPTIONS ${DEFAULT_C_COMPILE_FLAGS}
                LINK_LIBRARIES "${CMOCKA_LIBRARIES}" cryptopals_lib)

target_include_directories(analysis_test PRIVATE "${CMOCKA_INCLUDE_DIRS}" "${CMAKE_SOURCE_DIR}/include/analysis")
add_cmocka_test_environment(analysis_test)


#[[ == Crypto Tests == ]]

add_cmocka_test(crypto_test
                SOURCES crypto/aes_test.c "${CMAKE_SOURCE_DIR}/include/crypto"
                COMPILE_OPTIONS ${DEFAULT_C_COMPILE_FLAGS}
                LINK_LIBRARIES "${CMOCKA_LIBRARIES}" cryptopals_lib)

target_include_directories(crypto_test PRIVATE "${CMOCKA_INCLUDE_DIRS}" "${CMAKE_SOURCE_DIR}/include/crypto")
add_cmocka_test_environment(crypto_test)


#[[ == Set 1 Challenges Tests == ]]

add_cmocka_test(set1_test
                SOURCES challenges/set1_test.c "${CMAKE_SOURCE_DIR}/include/challenges"
                COMPILE_OPTIONS ${DEFAULT_C_COMPILE_FLAGS}
                LINK_LIBRARIES "${CMOCKA_LIBRARIES}" cryptopals_lib)


add_cmocka_test_environment(set1_test)
target_include_directories(set1_test PRIVATE "${CMOCKA_INCLUDE_DIRS}" "${CMAKE_SOURCE_DIR}/include")
