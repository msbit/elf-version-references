#include "example.h"

__asm__(".symver example,example@");
//__asm__(".symver example,example@EXAMPLE_1.1");
//__asm__(".symver example,example@EXAMPLE_1.2");
//__asm__(".symver example,example@EXAMPLE_2.0");

int main() {
  example();
  return (0);
}
