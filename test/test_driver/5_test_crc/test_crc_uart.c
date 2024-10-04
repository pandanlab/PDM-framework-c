#include "../../../hardware/stm32f103c8t6/driver/rcc/rcc.h"
#include "../../../hardware/stm32f103c8t6/driver/gpio/gpio.h"
#include "../../../hardware/stm32f103c8t6/driver/uart/uart.h"
#include "../../../hardware/stm32f103c8t6/driver/nvic/nvic.h"
#include "../../../hardware/stm32f103c8t6/driver/crc/crc.h"

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
    USART1->BRR = (4 << 4) | 5; // Đảm bảo tốc độ baudrate chính xác
    USART1->CR1 |= (1 << 3);     // Transmitter enable (TE)
    USART1->CR1 |= (1 << 2);     // Receiver enable (RE)
    USART1->CR1 |= (1 << 13);    // Uart enable (UE)
}

void usart_writeByte(uint8_t data){
    while((USART1->SR & (1<<7)) == 0);
    USART1->DR = data;
    while((USART1->SR & (1<<6)) == 0);
}


void usart_writeString(uint8_t *pTxBuffer, uint32_t index) {
	for(uint32_t count = 0; count < index; count ++){
		while((USART1->SR & (1<<7)) == 0);
		USART1->DR = pTxBuffer[count];
	}
	while((USART1->SR & (1<<6)) == 0);
}

void usart_readString(uint8_t* pRxBuffer, uint32_t* index, uint32_t len){
	uint32_t timeout = 0;
	uint32_t sw      = 0;
	for(uint32_t count = 0; count < len; count++){
		while((USART1->SR & (1<<5)) == 0){
			timeout++;
			if(timeout==10000) {
				sw = 1;
                *index = count; 
				break;
			}
		}
        if(sw == 1) {
            break;
        }
        else{
            pRxBuffer[count] = (uint8_t)(USART1->DR);
            *index = count;
        }

	}
	USART1->SR &= ~(1<<5);
}

uint32_t CRC_init(){
    RCC->AHBENR |=(1<<6);
}

uint32_t CRC_caculator(uint8_t* data, uint32_t len){
    CRC->CR |=(1<<0);
    for(uint32_t i=0; i<len; i++){
        CRC->DR = *data;
        data++;
    }
    return CRC->DR;
}

void USART1_IRQHandler(){

}


int main() {
    uint8_t RxBuffer[200];
    uint32_t index_buffer = 200;
    usart1_Init();
    CRC_init();
    usart_writeString("Hello World\n",12);
    while (1) {
        if((USART1->SR & (1<<5)) != 0){
            usart_readString(RxBuffer,&index_buffer,200);
            uint32_t mode = *(uint32_t *)RxBuffer;
            if(mode == 1){
                usart_writeString("oke",4);
                uint32_t crc_host  = *(uint32_t*)(RxBuffer+index_buffer-4);
                uint32_t crc_slave = CRC_caculator(RxBuffer,index_buffer-4);
                if(crc_host == crc_slave){
                    usart_writeString("dung",5);
                }
                else{
                    usart_writeString("sai",4);
                }
            }
            else{
                usart_writeString("no ",4);
            }
        }
    }

    return 0;
}
