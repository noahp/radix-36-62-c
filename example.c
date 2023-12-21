#include <stdio.h>

#include "r36_62.h"

int main() {
  char buf[14];

  r36_encode(buf, 4294967295);
  printf("%s\n", buf);  // 3z141z1

  r62_encode(buf, 4294967295);
  printf("%s\n", buf);  // 3cfFG4

  printf("%lu\n", r62_decode(buf));  // 4294967295

  return 0;
}
