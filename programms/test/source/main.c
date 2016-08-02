#include <stdint.h>

int hallo = 0;

int main(void)
{
  for (uint8_t i = 0; i < 100; i++) {
    hallo += i;
  }
  return hallo;
}
