#[[ == Smoke Test == ]]

add_cmocka_test(
    smoke_test
    SOURCES smoke_test.c
    COMPILE_OPTIONS ${DEFAULT_C_COMPILE_FLAGS}
    LINK_LIBRARIES "${CMOCKA_LIBRARIES}"
)

add_cmocka_test_environment(smoke_test)


#[[ == Set 1 Challenges Tests == ]]

add_cmocka_test(set1_test
                SOURCES set1_test.c "${CMAKE_SOURCE_DIR}/include/set1"
                COMPILE_OPTIONS ${DEFAULT_C_COMPILE_FLAGS}
                LINK_LIBRARIES "${CMOCKA_LIBRARIES}" cryptopals_lib)

add_cmocka_test_environment(set1_test)
target_include_directories(set1_test PRIVATE "${CMOCKA_INCLUDE_DIRS}" "${CMAKE_SOURCE_DIR}/include/set1")

