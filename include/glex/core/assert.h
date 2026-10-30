//
// Created by changemaker on 10/30/26.
//
#ifndef GLEX_ASSERT_H
#define GLEX_ASSERT_H

#include <cstdio>
#include <cstdlib>

#ifdef NDEBUG
#define GLEX_ASSERT(cond) ((void)0)
#else
#define GLEX_ASSERT(cond)                                                \
    do {                                                                 \
        if (!(cond)) {                                                   \
            std::fprintf(stderr, "Assertion failed: %s (%s:%d)\n", #cond, \
                         __FILE__, __LINE__);                            \
            std::abort();                                                \
        }                                                                \
    } while (false)
#endif

#endif // GLEX_ASSERT_H
