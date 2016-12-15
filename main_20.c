#include "example.h"

__asm__(".symver example,example@EXAMPLE_2.0");

int main() {
  example();
  return (0);
}
