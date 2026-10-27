cmake_minimum_required(VERSION 3.25)
project(glex CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(glex src/main.cpp
        include/glex/math/vec2.h)
target_include_directories(glex PRIVATE include)
# Build gates (G8). Every target links this, so the flags live in one place (G1).
add_library(glex_gates INTERFACE)
target_compile_options(glex_gates INTERFACE
        -Wall -Wextra -Wpedantic -Wshadow -Wconversion -Werror
        $<$<CONFIG:Debug>:-fsanitize=address,undefined -fno-omit-frame-pointer>)
target_link_options(glex_gates INTERFACE
        $<$<CONFIG:Debug>:-fsanitize=address,undefined>)

target_link_libraries(glex PRIVATE glex_gates)


# Tests (D-003: GoogleTest)
include(FetchContent)
FetchContent_Declare(googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG v1.17.0
        GIT_SHALLOW TRUE
        SYSTEM)
set(INSTALL_GTEST OFF CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()
add_executable(glex_tests tests/math/vec2_test.cpp)
target_include_directories(glex_tests PRIVATE include)
target_link_libraries(glex_tests PRIVATE glex_gates GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(glex_tests)