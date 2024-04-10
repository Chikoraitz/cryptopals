cmake_minimum_required(VERSION 3.13)
project(cryptopals VERSION 0.1.0)

# Add source files
add_subdirectory(src)

# Add CMocka CMake modules
set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmocka)

if(UNIT_TESTING)
  find_package(cmocka REQUIRED)
  include(FindCMocka)
  include(AddCMockaTest)
  add_subdirectory(tests)
  enable_testing()
endif(UNIT_TESTING)

add_executable(main main.c)
target_link_libraries(main PRIVATE cryptopals_lib)