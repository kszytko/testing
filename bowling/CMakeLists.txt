cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

##-----------------G-test SCRIPT FROM CODERS SCHOOL----------------##
#Download and unpack googletest at configure time
configure_file(CMakeLists.txt.in googletest-download/CMakeLists.txt)
execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download )
if(result)
  message(FATAL_ERROR "CMake step for googletest failed: ${result}")
endif()
execute_process(COMMAND ${CMAKE_COMMAND} --build .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download )
if(result)
  message(FATAL_ERROR "Build step for googletest failed: ${result}")
endif()

# Prevent overriding the parent project's compiler/linker
# settings on Windows
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

# Add googletest directly to our build. This defines
# the gtest and gtest_main targets.
add_subdirectory(${CMAKE_CURRENT_BINARY_DIR}/googletest-src
                     ${CMAKE_CURRENT_BINARY_DIR}/googletest-build
                     EXCLUDE_FROM_ALL)

# The gtest/gtest_main targets carry header search path
# dependencies automatically when using CMake 2.8.11 or
# later. Otherwise we have to add them here ourselves.
if (CMAKE_VERSION VERSION_LESS 2.8.11)
  include_directories("${gtest_SOURCE_DIR}/include")
endif()

##-----------------G-test SCRIPT FROM CODERS SCHOOL----------------##

project(bowling)

set(INCLUDE_DIR ${CMAKE_SOURCE_DIR}/inc)
set(SOURCE_DIR ${CMAKE_SOURCE_DIR}/src)
set(TEST_DIR ${CMAKE_SOURCE_DIR}/test)

include_directories(${INCLUDE_DIR})

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

##Insert project source files here.##
file(GLOB TEST_FILES ${TEST_DIR}/*.cpp)
file(GLOB SOURCES ${SOURCE_DIR}/*.cpp)

#SRC LIB
add_library(SRC_LIB STATIC ${SOURCES})

#MAIN
add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} ${SRC_LIB})
#target_compile_options(${PROJECT_NAME} PRIVATE -Wall -pedantic -O3)


# Tests
message("Generate tests:")

enable_testing()
foreach(TEST_FILE ${TEST_FILES})
  # Get name of file
  get_filename_component(TEST_FILE_NAME ${TEST_FILE} NAME_WE)
  # Create test name
  set(TEST_NAME Test_${TEST_FILE_NAME})

  message("${TEST_NAME} active")

  add_executable (${TEST_NAME} ${TEST_FILE} ${SRC_FILES})
  target_link_libraries(${TEST_NAME} gtest_main ${SRC_LIB})
  target_compile_options(${TEST_NAME} PRIVATE -Wall -Wextra -Werror -Wconversion -pedantic -O3)
  add_test(NAME ${TEST_NAME} COMMAND ${TEST_NAME})
ENDFOREACH()