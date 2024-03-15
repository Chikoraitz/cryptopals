cmake_minimum_required(VERSION 3.13)
project(cryptopals VERSION 0.1.0)

# Add source files
add_subdirectory(src)

# Add header files
add_subdirectory(include)

# Add CMocka CMake modules
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmocka)

if(UNIT_TESTING)
  find_package(cmocka REQUIRED)
  include(FindCMocka)
  include(AddCMockaTest)
  add_subdirectory(tests)
endif()

add_executable(set1 main.c)
target_link_libraries(set1 PUBLIC base64_lib)