#include <stdint.h>

//! Encode/decode base 36. Range of permitted chars:
//! 0-9, a-z
void r36_encode(char *buf, uint64_t value);
uint64_t r36_decode(const char *buf);

//! Encode/decode base 62. Range of permitted chars:
//! 0-9, a-z, A-Z
void r62_encode(char *buf, uint64_t value);
uint64_t r62_decode(const char *buf);
