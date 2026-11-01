//
// Created by changemaker on 10/30/26.
//
#pragma once

#include <cstdio>
#include <cstdlib>

// D-004, D-013: checked in debug, compiled out in release.
#ifdef NDEBUG
#define GLEX_ASSERT(cond) ((void)0)
#else
#include <stacktrace>
#include <string>
#define GLEX_ASSERT(cond)                                                 \
    do {                                                                  \
        if (!(cond)) {                                                    \
            std::fprintf(stderr, "Assertion failed: %s (%s:%d)\n%s\n",    \
                         #cond, __FILE__, __LINE__,                       \
                         std::to_string(std::stacktrace::current())       \
                             .c_str());                                   \
            std::abort();                                                 \
        }                                                                 \
    } while (false)
#endif
