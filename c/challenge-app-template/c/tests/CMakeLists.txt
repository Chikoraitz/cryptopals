list(APPEND TEST_TARGETS smoke_test)
list(APPEND TEST_TARGETS base64_test)


list(APPEND TEST_LIBS "${CMOCKA_LIBRARIES}")
list(APPEND TEST_LIBS base64_lib)

list(APPEND TEST_DIRS "${CMOKCA_INCLUDE_DIRS}")
list(APPEND TEST_DIRS "${convertHex2Base64}/src")

foreach(TEST_TARGET ${TEST_TARGETS})
  add_cmocka_test(
    ${TEST_TARGET}
    SOURCES "${TEST_TARGET}.c"
    COMPILE_OPTIONS ${DEFAULT_C_COMPILE_FLAGS}
    LINK_LIBRARIES "${TEST_LIBS}"
  )
  add_cmocka_test_environment(${TEST_TARGET})
  target_include_directories(${TEST_TARGET} PUBLIC "${TEST_DIRS}")

endforeach()


