#include <stdint.h>

typedef struct {
  volatile uint32_t CR;
  volatile uint32_t RESERVED[11];
  volatile uint32_t AHB1ENR;
  volatile uint32_t RESERVED2[4];
  volatile uint32_t APB2ENR;
} RCC_TypeDef;

#define RCC_BASE_ADDRESS 0x40023800
#define RCC ((RCC_TypeDef*)RCC_BASE_ADDRESS)

typedef struct {
  volatile uint32_t MODER;
  volatile uint32_t RESERVED[5];
  volatile uint32_t BSRR;
  volatile uint32_t RESERVED2[2];
  volatile uint32_t AFRH;
} GPIO_TypeDef;

#define GPIO_BASE_ADDRESS 0x40020000
#define GPIOA ((GPIO_TypeDef*)GPIO_BASE_ADDRESS)

typedef struct {
  volatile uint32_t SR;
  volatile uint32_t DR;
  volatile uint32_t BRR;
  volatile uint32_t CR1;
  volatile uint32_t CR2;
  volatile uint32_t CR3;
  volatile uint32_t GTPR;
} USART_TypeDef;

#define USART_BASE_ADDRESS 0x40011000
#define USART1 ((USART_TypeDef*)USART_BASE_ADDRESS)

typedef struct {
  volatile uint32_t CR;
  volatile uint32_t NDTR;
  volatile uint32_t PAR;
  volatile uint32_t M0AR;
  volatile uint32_t M1AR;
  volatile uint32_t FCR;
} DMA_Stream_TypeDef;

typedef struct {
  volatile uint32_t LISR;
  volatile uint32_t HISR;
  volatile uint32_t LIFCR;
  volatile uint32_t HIFCR;
  volatile DMA_Stream_TypeDef Streams[8];
} DMA_TypeDef;

#define DMA2_BASE_ADDRESS 0x40026400
#define DMA2 ((DMA_TypeDef*)DMA2_BASE_ADDRESS)

typedef struct {
  volatile uint32_t ISER[8];
} NVIC_TypeDef;

#define NVIC_BASE_ADDRESS 0xE000E100
#define NVIC ((NVIC_TypeDef*)NVIC_BASE_ADDRESS)

typedef struct {
  volatile uint32_t CTRL;
  volatile uint32_t LOAD;
  volatile uint32_t VAL;
  volatile uint32_t CALIB;
} STK_TypeDef;

#define STK_BASE_ADDRESS 0xE000E010
#define STK ((STK_TypeDef*)STK_BASE_ADDRESS)