#include "../../../hardware/stm32f103c8t6/driver/rcc/rcc.h"
#include "../../../hardware/stm32f103c8t6/driver/gpio/gpio.h"
#include "../../../hardware/stm32f103c8t6/driver/uart/uart.h"
#include "../../../hardware/stm32f103c8t6/driver/nvic/nvic.h"

uint8_t RxBuffer[200];
uint32_t index_buffer = 200;

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

    // Reset DR
    USART1->DR = 0;

    // Bat ngat UART
   NVIC_EnableIRQ(37);          // Kiểm tra số IRQ cho USART1 position 37
}

void usart_writeString(uint8_t *pTxBuffer, uint32_t index) {
	for(uint32_t count = 0; count < index; count ++){
		while((USART1->SR & (1<<7)) == 0);
		USART1->DR = pTxBuffer[count];
	}
	while((USART1->SR & (1<<6)) == 0);
}

void usart_readString(uint8_t* pRxBuffer, uint32_t* index, uint32_t len){
	uint32_t count_timeout = 0;
	uint32_t sw            = 0;
	for(uint32_t count = 0; count < len; count++){
		while((USART1->SR & (1<<5)) == 0){
			count_timeout++;
			if(count==count_timeout) {
				sw = 1;
                *index = count; 
				break;
			}
		}
        if(sw == 1) break;
        else{
            pRxBuffer[count] = (uint8_t)(USART1->DR);
            *index = count;
        }
	}
	USART1->SR &= ~(1<<5);
}

void usart_writeByte(uint8_t data){
    while((USART1->SR & (1<<7)) == 0);
    USART1->DR = data;
    while((USART1->SR & (1<<6)) == 0);
}

void USART1_IRQHandler(){
    if((USART1->SR & (1<<5)) != 0){
        usart_readString(RxBuffer, &index_buffer, 200);
        usart_writeString(RxBuffer, index_buffer);
    }
}



int main() {
    usart1_Init();
    usart_writeString("Hello\n",100);
    while (1) {
    }

    return 0;
}
