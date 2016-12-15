#include "example.h"

__asm__(".symver example,example@EXAMPLE_1.1");

int main() {
  example();
  return (0);
}
