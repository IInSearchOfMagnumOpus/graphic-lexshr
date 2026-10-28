# graphic-lexshr

A Vulkan graphics engine with a math-first, animator-facing API, written in C++23.

A ground-up port of [gLexShrD](https://github.com/RITIKESHDUTT/gLexShrD): same goals, redesigned along the way.


<p align="center">
<img src="https://img.shields.io/badge/language-C%2B%2B23-00599C?logo=cplusplus&logoColor=white"/>
<img src="https://img.shields.io/badge/backend-Vulkan_1.3-AC162C?logo=vulkan&logoColor=white"/>
<img src="https://img.shields.io/badge/architecture-Math--First-8B5CF6"/>
<img src="https://img.shields.io/badge/status-WIP-F59E0B"/>
<img src="https://img.shields.io/badge/license-Apache%202.0-3B82F6"/><br>
<img src="https://github.com/IInSearchOfMagnumOpus/graphic-lexshr/actions/workflows/ci.yml/badge.svg"/>
</p>

## Status

Early. The toolchain and quality gates are in place; the math core is next.

For a peek into active development and ongoing work:
- [Issue Tracker](https://github.com/IInSearchOfMagnumOpus/graphic-lexshr/issues)

![Issues](https://img.shields.io/github/issues/IInSearchOfMagnumOpus/graphic-lexshr)
![Closed Issues](https://img.shields.io/github/issues-closed/IInSearchOfMagnumOpus/graphic-lexshr)

| Stage | What | State |
|---|---|---|
| A | Foundation: toolchain, gates, math core | In progress |
| B | First slice: an animated quad in a window | Not started |
| C | Widen: memory, sync, frame graph, renderer, animation | Not started |
| D | Demo and write-up | Not started |

## Build and test

Requirements: CMake 3.25+, a C++23 compiler (tested with GCC 16), `clang-tidy`.
GoogleTest is downloaded automatically on first configure.

```sh
cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug
cmake --build build
ctest --test-dir build --output-on-failure
```

## Quality gates

Every build enforces these; a failing gate stops the build.

- **Warnings are errors:** `-Wall -Wextra -Wpedantic -Wshadow -Wconversion -Werror`
- **Sanitizers (Debug):** AddressSanitizer and UndefinedBehaviorSanitizer
- **Static analysis:** clang-tidy (`bugprone-*`, `clang-analyzer-*`) on every build
- **Tests:** GoogleTest through CTest
