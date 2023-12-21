#include "r36_62.h"

#include <stdint.h>
#include <string.h>

const char r62_alphabet[] =
    "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";

const char r36_alphabet[] = "0123456789abcdefghijklmnopqrstuvwxyz";

#define RADIX_ENCODE(radix_)                           \
  void r##radix_##_encode(char *buf, uint64_t value) { \
    uint64_t remainder = 0;                            \
    uint64_t quotient = value;                         \
    uint64_t index = 0;                                \
    while (quotient > 0) {                             \
      remainder = quotient % radix_;                   \
      quotient = quotient / radix_;                    \
      buf[index] = r##radix_##_alphabet[remainder];    \
      index++;                                         \
    }                                                  \
    buf[index] = '\0';                                 \
  }

#define RADIX_DECODE(radix_)                                   \
  uint64_t r##radix_##_alphabet_index(char c) {                \
    for (uint64_t i = 0; i < radix_; i++) {                    \
      if (r##radix_##_alphabet[i] == c) {                      \
        return i;                                              \
      }                                                        \
    }                                                          \
    return 0;                                                  \
  }                                                            \
  uint64_t r##radix_##_decode(const char *buf) {               \
    uint64_t value = 0;                                        \
    int index = strlen(buf) - 1; /* start at the end */        \
    uint64_t power = 1;                                        \
    while (index >= 0) {                                       \
      value += r##radix_##_alphabet_index(buf[index]) * power; \
      power *= radix_;                                         \
      index--;                                                 \
    }                                                          \
    return value;                                              \
  }

RADIX_ENCODE(62)
RADIX_DECODE(62)
RADIX_ENCODE(36)
RADIX_DECODE(36)
