#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "r36_62.h"

int main(int argc, char **argv) {
  if (argc != 4) {
    printf("Usage: %s <radix> <encode|decode> <value>\n", argv[0]);
    return 1;
  }

  int radix = atoi(argv[1]);
  if (radix != 36 && radix != 62) {
    printf("Radix must be 36 or 62\n");
    return 1;
  }

  if (strcmp(argv[2], "encode") == 0) {
    uint64_t value = strtoull(argv[3], NULL, 0);
    char buf[13];
    if (radix == 36) {
      r36_encode(buf, value);
    } else {
      r62_encode(buf, value);
    }
    printf("%s\n", buf);
  } else if (strcmp(argv[2], "decode") == 0) {
    uint64_t value;
    if (radix == 36) {
      value = r36_decode(argv[3]);
    } else {
      value = r62_decode(argv[3]);
    }
    printf("%" PRIu64 "\n", value);
  } else {
    printf("Unknown command: %s\n", argv[2]);
    return 1;
  }
}
