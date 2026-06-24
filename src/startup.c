#include <stdint.h>

volatile uint32_t _estack;
volatile uint32_t _sdata;
volatile uint32_t _sidata;
volatile uint32_t _edata;
volatile uint32_t _sbss;
volatile uint32_t _ebss;

extern int main(void);
void Reset_Handler(void);
extern void USART1_IRQHandler(void);

uint32_t vectors[56] __attribute__((section(".isr_vector"))) = {
    (uint32_t)&_estack, (uint32_t)Reset_Handler, [53] = (uint32_t) USART1_IRQHandler};

void Reset_Handler(void) {
  volatile uint32_t* data_ram_ptr = &_sdata;
  volatile uint32_t* data_flash_ptr = &_sidata;

  while (data_ram_ptr < &_edata) {
    *data_ram_ptr = *data_flash_ptr;
    data_ram_ptr++;
    data_flash_ptr++;
  }

  volatile uint32_t* bss_ptr = &_sbss;

  while (bss_ptr < &_ebss) {
    *bss_ptr = 0;
    bss_ptr++;
  }

  main();
}