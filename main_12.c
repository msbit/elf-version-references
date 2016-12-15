#include "example.h"

__asm__(".symver example,example@EXAMPLE_1.2");

int main() {
  example();
  return (0);
}
