#ifndef UART_H
#define UART_H

#include <stdint.h>
#include "../../../../hardware/stm32f103c8t6/driver/gpio/gpio.h"
#include "../../../../hardware/stm32f103c8t6/driver/rcc/rcc.h"

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

void uart_init(UART_Types * USART,GPIO_Types * GPIO, uint8_t pin_TX, uint8_t pin_RX);
uint8_t uart_statusRead(UART_Types * USART);
uint8_t uart_statusWrite(UART_Types * USART);
void uart_resetWrite(UART_Types * USART);
void uart_resetRead(UART_Types * USART);
void uart_write(UART_Types * USART,uint8_t data);
uint8_t uart_read(UART_Types * USART);

#endif // UART_H
