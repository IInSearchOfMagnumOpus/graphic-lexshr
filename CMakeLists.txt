cmake_minimum_required(VERSION 3.25)
project(glex C CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(glex src/main.cpp)
target_include_directories(glex PRIVATE include)

# Build gates (G8). Every target links this, so the flags live in one place (G1).

add_library(glex_gates INTERFACE)
target_compile_options(glex_gates INTERFACE
        -Wall -Wextra -Wpedantic -Wshadow -Wconversion -Werror
        $<$<CONFIG:Debug>:-fsanitize=address,undefined -fno-omit-frame-pointer>)
target_link_options(glex_gates INTERFACE
        $<$<CONFIG:Debug>:-fsanitize=address,undefined>)

target_link_libraries(glex PRIVATE glex_gates)
target_link_libraries(glex_gates INTERFACE $<$<CONFIG:Debug>:stdc++exp>)

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
add_executable(glex_tests
        tests/math/vec2_test.cpp
        tests/math/scalar_test.cpp
        tests/math/point2_test.cpp
        tests/math/rect2_test.cpp
)
target_include_directories(glex_tests PRIVATE include)
target_link_libraries(glex_tests PRIVATE glex_gates GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(glex_tests)

# Static analysis (G6). clang-tidy runs alongside the compiler on our own targets.
find_program(CLANG_TIDY clang-tidy REQUIRED)
set_target_properties(glex glex_tests PROPERTIES CXX_CLANG_TIDY ${CLANG_TIDY})


# Windowing (D-005): raw Wayland. xdg-shell is generated, never hand-written.
find_package(PkgConfig REQUIRED)
pkg_check_modules(WAYLAND REQUIRED IMPORTED_TARGET wayland-client)
pkg_get_variable(WAYLAND_PROTOCOLS_DIR wayland-protocols pkgdatadir)
find_program(WAYLAND_SCANNER wayland-scanner REQUIRED)

set(XDG_SHELL_XML ${WAYLAND_PROTOCOLS_DIR}/stable/xdg-shell/xdg-shell.xml)
set(GEN_DIR ${CMAKE_CURRENT_BINARY_DIR}/protocols)
add_custom_command(
        OUTPUT ${GEN_DIR}/xdg-shell-client-protocol.h ${GEN_DIR}/xdg-shell-protocol.c
        COMMAND ${CMAKE_COMMAND} -E make_directory ${GEN_DIR}
        COMMAND ${WAYLAND_SCANNER} client-header ${XDG_SHELL_XML} ${GEN_DIR}/xdg-shell-client-protocol.h
        COMMAND ${WAYLAND_SCANNER} private-code ${XDG_SHELL_XML} ${GEN_DIR}/xdg-shell-protocol.c
        DEPENDS ${XDG_SHELL_XML}
        VERBATIM)

add_library(glex_wayland_protocols STATIC ${GEN_DIR}/xdg-shell-protocol.c)
target_include_directories(glex_wayland_protocols SYSTEM PUBLIC ${GEN_DIR})
target_link_libraries(glex_wayland_protocols PUBLIC PkgConfig::WAYLAND)