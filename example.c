#include <stdio.h>

__asm__(".symver example_10,example@");
__asm__(".symver example_11,example@EXAMPLE_1.1");
__asm__(".symver example_12,example@EXAMPLE_1.2");
__asm__(".symver example_20,example@@EXAMPLE_2.0");

void example_10() { printf("example\n"); }

void example_11() { printf("example_11\n"); }

void example_12() { printf("example_12\n"); }

void example_20() { printf("example_20\n"); }
