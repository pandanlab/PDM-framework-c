#include "../../../hardware/stm32f103c8t6/driver/rcc/rcc.h"
#include "../../../hardware/stm32f103c8t6/driver/gpio/gpio.h"
#include "../../../hardware/stm32f103c8t6/driver/uart/uart.h"
#include "../../../software/layer_unit/unit_delay/unit_delay.h"
#include "../../../hardware/stm32f103c8t6/driver/nvic/nvic.h"

void usart1_Init(void) {
    // Bat xung clock
    RCC->APB2ENR |= (1 << 2);      // bat xung clock gpioA
    RCC->APB2ENR |= (1 << 14);     // bat xung clock uart1

    // Cau hinh chan gpio 
    // PA9/TX - output/alternate-pushpull
    GPIOA->CRH |= (1 << 4);
    GPIOA->CRH &= ~(1 << 5);
    GPIOA->CRH &= ~(1 << 6);
    GPIOA->CRH |= (1 << 7);

    // PA10/RX - input/float
    GPIOA->CRH &= ~(1 << 8);
    GPIOA->CRH &= ~(1 << 9);
    GPIOA->CRH |= (1 << 10);
    GPIOA->CRH &= ~(1 << 11);

    // Cau hinh uart1
    USART1->BRR = (52 << 4) | 1; // Đảm bảo tốc độ baudrate chính xác
    USART1->CR1 |= (1 << 3);     // Transmitter enable (TE)
    USART1->CR1 |= (1 << 2);     // Receiver enable (RE)
    USART1->CR1 |= (1 << 5);     // Enable RXNE interrupt

    USART1->CR1 |= (1 << 13);    // Uart enable (UE)

    // Bat ngat UART
    NVIC_EnableIRQ(37);          // Kiểm tra số IRQ cho USART1 position 37
}

void UART1_IRQHandler(){
    uint8_t data = USART1->DR;
    USART1->SR = 0;
} 

void usart1Send(uint8_t data) {
    USART1->DR = data;
    while (!((USART1->SR & (1 << 6))>>6)); 
    USART1->SR &= ~(1<<6);
}

int main() {
    usart1_Init();

    while (1) {
        for(int i = 0; i < 10; i++){
            usart1Send('A'+ i);
        }
        delay(1000);
    }

    return 0;
}
