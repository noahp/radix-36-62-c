# Radix-36 and Radix-62 Conversion in C

Convert between decimal and radix-36 / radix-62 in C, aka "hexatridecimal" and
"duosexagesimal" respectively.

## Usage

```c
#include "r36_62.h"

#include <stdio.h>

int main() {
    char buf[14];

    r36_encode(buf, 4294967295);
    printf("%s\n", buf); // 3z141z1

    r62_encode(buf, 4294967295);
    printf("%s\n", buf); // 3cfFG4

    char input[] = "3cfFG4";
    printf("%lu\n", r62_decode(input)); // 4294967295

    return 0;
}
```

Experimental only, there's no sanitization or range checking.
