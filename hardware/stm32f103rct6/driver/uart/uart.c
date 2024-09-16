#include "uart.h"

void uart_initHardware(GPIO_Types * GPIO, uint8_t pin_TX, uint8_t pin_RX){
    pinMode(GPIO,pin_TX,OUTPUT,ALTERNATE_PUSHPULL_OUTPUT);
    pinMode(GPIO,pin_RX,INPUT,FLOAT_INPUT);
}

void uart_initSoftware(UART_Types * USART){
    USART->BRR = (52UL<<4) | 1;
    USART->CR1 = (1<<13)|(1<<5)|(1<<3)|(1<<2); 
}

uint8_t uart_statusRead(UART_Types * USART){ 
    return ((USART->SR & (1<<5))>>5);
}
uint8_t uart_statusWrite(UART_Types * USART){
    return ((USART->SR & (1<<6))>>6);
}

void uart_resetRead(UART_Types * USART){
    USART->SR &=~(1<<5);
}

void uart_resetWrite(UART_Types * USART){
    USART->SR |=(1<<6);
}

void uart_write(UART_Types * USART, uint8_t data){
    USART->DR = data;
    while(!uart_statusWrite(USART));
    uart_resetWrite(USART1);
    
}

uint8_t uart_read(UART_Types * USART){
    while(!uart_statusRead(USART));
    uint8_t data = USART->DR;
    uart_resetRead(USART1);
    return data;
}
