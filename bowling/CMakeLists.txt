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
set(SOURCES
    ${SOURCE_DIR}/game.cpp
    ${SOURCE_DIR}/filesReader.cpp
    ${SOURCE_DIR}/argumentParser.cpp
    ${SOURCE_DIR}/frameParser.cpp
    ${SOURCE_DIR}/tokenizer.cpp
    ${SOURCE_DIR}/printer.cpp
    ${SOURCE_DIR}/lane.cpp
    ${SOURCE_DIR}/scoreCounter.cpp
)

set(TESTS
    ${TEST_DIR}/bowling-ut.cpp
    ${TEST_DIR}/filesReader-ut.cpp
    ${TEST_DIR}/argumentParser-ut.cpp
    ${TEST_DIR}/parser-ut.cpp
    ${TEST_DIR}/printer-ut.cpp
)

add_library(${PROJECT_NAME}-lib STATIC ${SOURCES})

add_executable(${PROJECT_NAME} ${SOURCE_DIR}/main.cpp)
add_executable(${PROJECT_NAME}-ut ${TESTS})

target_link_libraries(${PROJECT_NAME} ${PROJECT_NAME}-lib)
target_link_libraries(${PROJECT_NAME}-ut ${PROJECT_NAME}-lib gtest_main stdc++fs)

target_link_libraries(${PROJECT_NAME} ${PROJECT_NAME}-lib)
target_link_libraries(${PROJECT_NAME}-ut ${PROJECT_NAME}-lib gtest_main)

target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -Werror -Wconversion -pedantic -O3)
target_compile_options(${PROJECT_NAME}-ut PRIVATE -Wall -Wextra -Werror -Wconversion -pedantic -O3)
enable_testing()
add_test(NAME BowlingTest COMMAND ${PROJECT_NAME}-ut)
