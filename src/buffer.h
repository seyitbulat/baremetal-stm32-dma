#include <stdint.h>
#define RX_BUFFER_SIZE 64


typedef struct
{
    char buffer[RX_BUFFER_SIZE];
    volatile uint32_t head;
    volatile uint32_t tail;
}RingBuffer_t;


