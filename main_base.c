#include "example.h"

__asm__(".symver example,example@");

int main() {
  example();
  return (0);
}
