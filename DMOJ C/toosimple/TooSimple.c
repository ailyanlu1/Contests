#include <stdio.h>
#include <stdlib.h>

#define print(...) puts(#__VA_ARGS__)

int main() {
    print(Hello, World!);
}
