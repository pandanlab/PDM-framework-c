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

#define UART1_BASEADDR   0x40013800
#define UART1            ((UART_Types *) UART1_BASEADDR)

// Định nghĩa các bit trong thanh ghi CR1 của USART
#define USART_CR1_UE   (1 << 13) // UART Enable
#define USART_CR1_TE   (1 << 3)  // Transmitter Enable
#define USART_CR1_RE   (1 << 2)  // Receiver Enable
#define USART_CR1_M    (1 << 12) // Word Length (0: 8 bits, 1: 9 bits)
#define USART_CR1_PCE  (1 << 10) // Parity Control Enable
#define USART_CR1_PS   (1 << 9)  // Parity Selection (0: Even, 1: Odd)

// Định nghĩa các bit trong thanh ghi SR của USART
#define USART_SR_TXE  (1 << 7)  // Transmit Data Register Empty
#define USART_SR_RXNE (1 << 5)  // Read Data Register Not Empty

void UART_Init(void);
void UART_SendData(uint8_t * pTXBuffer, uint32_t len);
void UART_ReceiveData(uint8_t * pRXBuffer, uint32_t len);

#endif // UART_H
