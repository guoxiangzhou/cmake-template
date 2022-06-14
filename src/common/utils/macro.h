#pragma once

#include <memory.h>
#include <stdint.h>

#define BZERO_ARRAY(buf) memset(buf, 0, sizeof(buf))
#define BZERO_STRUCT(buf) memset(&buf, 0, sizeof(buf))

#define LERP(a, b, r)                                                          \
  (((r) >= 1) ? (b) : (((r) <= 0) ? (a) : ((a) + (r) * ((b) - (a)))))

#define MIN(a, b) (((a) < (b)) ? (a) : (b))
#define MAX(a, b) (((a) > (b)) ? (a) : (b))
#define CORRECT(val, a, b) (val = MAX((a), val), val = MIN(val, (b)))

#define EXCHANGE(a, b, T)                                                      \
  do {                                                                         \
    T t = a;                                                                   \
    a = b;                                                                     \
    b = t;                                                                     \
  } while (0)
