#include <stdio.h>

#include "r36_62.h"

int main() {
  char buf[14];

  r36_encode(buf, 4294967295);
  printf("%s\n", buf);  // 1z141z3

  printf("%lu\n", r36_decode(buf));  // 4294967295

  r62_encode(buf, 4294967295);
  printf("%s\n", buf);  // 4GFfc3

  printf("%lu\n", r62_decode(buf));  // 4294967295

  return 0;
}
