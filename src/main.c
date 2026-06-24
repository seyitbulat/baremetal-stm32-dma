#include "buffer.h"
#include "regs.h"

RingBuffer_tr rx_buffer = {.head = 0, .tail = 0};

void usart_send_string(char* str);
void usart_send_char(char c);
char usart_recieve_byte(void);
void usart_dma_transmit(char* str);
void USART1_IRQHandler(void);

void ring_buffer_write(char c);
char ring_buffer_read(void);


int main(void) {
  // set rcc gpio pin enabled
  RCC->AHB1ENR &= ~(1 << 0);  // reset gpioa clock
  RCC->AHB1ENR |= (1 << 0);   // enable gpioa clock

  // set rcc usart1 pin
  RCC->APB2ENR &= ~(1 << 4);  // reset rcc usart1 clock
  RCC->APB2ENR |= (1 << 4);   // set rcc usart1 clock

  // set gpioa pa9 and pa10 pin to alternate mod
  GPIOA->MODER &= ~(0xF << 18);  // reset gpio pins
  GPIOA->MODER |= (0xA << 18);   // set pins to alternate function mode

  // set gpio pa9 and pa10 pin to AF7
  GPIOA->AFRH &= ~(0xFF << 4);  // reset AFRH PA9 and PA10
  GPIOA->AFRH |= (0x77 << 4);   // set AF7 to PA9 and PA10

  // set 115200 baudrate
  // Mantissa 8 -> 0x8
  // Fraction 11 -> 0xB
  USART1->BRR = (0x8 << 4) | 0xB;

  // set usart1 enable
  USART1->CR1 |= (0b11 << 2);
  USART1->CR1 |= 1 << 13;

  // RCC DMA2 enable
  RCC->AHB1ENR |= 1 << 22;

  // set dma channel to 4
  DMA2->Streams[7].CR |= (0b100 << 25);
  // set dir memory-to-peripheral
  DMA2->Streams[7].CR |= (0b01 << 6);

  // set minc to increment mode
  DMA2->Streams[7].CR |= (1 << 10);

  // set pinc to fixed mode
  DMA2->Streams[7].CR &= ~(1 << 9);

  // set par Usart1 DR register address
  DMA2->Streams[7].PAR = (uint32_t)&USART1->DR;

  // set usart dma pin enable
  USART1->CR3 |= (1 << 7);

  // set enable recieve interrupt enabled
  USART1->CR1 |= (1 << 5);

  // set nvic 37 usart1 interrupt
  NVIC->ISER[1] |= (1 << 5);

 
  
  while (1) {
    if(rx_buffer.head != rx_buffer.tail){
      char data = ring_buffer_read();
      usart_send_char(data);
    }
  }
}

void usart_send_string(char* str) {
  while (*str != '\0') {
    while (!((USART1->SR >> 7) & 0x01));

    USART1->DR = *str;
    str++;
  }
}

void usart_send_char(char c) {
  while (!((USART1->SR >> 7) & 0x01));

  USART1->DR = c;
}

char usart_recieve_byte(void) {
  while (!((USART1->SR >> 5) & 0x01));

  char c = USART1->DR;
  return c;
}

void usart_dma_transmit(char* str) {
  DMA2->Streams[7].CR &= ~(1 << 0);
  DMA2->HIFCR |= (1 << 27);

  uint32_t len = 0;
  while (*str != '\0') {
    len++;
    str++;
  }

  str -= len;
  DMA2->Streams[7].NDTR = len;

  DMA2->Streams[7].M0AR = (uint32_t)str;

  DMA2->Streams[7].CR |= 1 << 0;
}

void USART1_IRQHandler(void) {
  if (((USART1->SR >> 5) & 0x01)) {
    char data = (char)(USART1->DR);

    ring_buffer_write(data);
  }
}

void ring_buffer_write(char c) {
  rx_buffer.buffer[rx_buffer.head] = c;
  rx_buffer.head = (rx_buffer.head + 1) % RX_BUFFER_SIZE;
}


char ring_buffer_read(void){
  char c = rx_buffer.buffer[rx_buffer.tail];

  rx_buffer.tail = (rx_buffer.tail + 1) % RX_BUFFER_SIZE;

  return c;
}