#include "pmm.h"

#define MAP 32 // 128 bei 1k Size
#define SIZE 1024
static uint32_t bitmap;
static uint8_t memory [MAP * SIZE];

void pmm_init()
{

}

uint8_t* pmm_alloc()
{
  for (uint8_t i = 0; i < MAP; i++) {
    if ((bitmap & (1<<i)) == 0) {
      bitmap |= 1 << i;

      return &memory[i * SIZE];
    }
  }

  return 0x00;
}
void pmm_free(uint8_t* page)
{
  bitmap &= ~((page - &memory[0])/SIZE);
}
