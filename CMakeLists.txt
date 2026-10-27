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