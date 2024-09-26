#ifndef UART_H
#define UART_H

#include <stdint.h>

typedef struct
{
    volatile uint32_t SR;
    volatile uint32_t DR;
    volatile uint32_t BRR;
    volatile uint32_t CR1;
    volatile uint32_t CR2;
    volatile uint32_t CR3;
    volatile uint32_t GTPR;
} UART_Types;

#define USART1_BASEADDR   0x40013800
#define USART1            ((UART_Types *) USART1_BASEADDR)

#define USART2_BASEADDR   0x40004400
#define USART2            ((UART_Types *) USART1_BASEADDR)

#define USART3_BASEADDR   0x40004800
#define USART3            ((UART_Types *) USART1_BASEADDR)

#endif // UART_H