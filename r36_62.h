#include <stdint.h>

#define RADIX_FUNCTIONS_(radix_)                      \
  void r##radix_##_encode(char *buf, uint64_t value); \
  uint64_t r##radix_##_decode(const char *buf);

RADIX_FUNCTIONS_(62)
RADIX_FUNCTIONS_(36)
