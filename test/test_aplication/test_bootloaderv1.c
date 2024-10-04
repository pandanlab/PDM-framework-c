#include "../../hardware/stm32f103c8t6/driver/rcc/rcc.h"
#include "../../hardware/stm32f103c8t6/driver/gpio/gpio.h"
#include "../../hardware/stm32f103c8t6/driver/uart/uart.h"
#include "../../hardware/stm32f103c8t6/driver/nvic/nvic.h"
#include "../../hardware/stm32f103c8t6/driver/crc/crc.h"
#include "../../hardware/stm32f103c8t6/driver/flash/flash.h"
#include "../../software/layer_unit/unit_boot/unit_boot.h"

void usart1_Init(void) {
    // Bat xung clock
    RCC->APB2ENR |= (1 << 2);      // bat xung clock gpioA
    RCC->APB2ENR |= (1 << 14);     // bat xung clock uart1

    // Cau hinh chan gpio
    //PA8-> Input pullup,pulldow
    GPIOA->CRH &= ~(1<<0);
    GPIOA->CRH &= ~(1<<1);
    GPIOA->CRH &= ~(1<<2);
    GPIOA->CRH |= (1<<3);
    GPIOA->ODR |= (1<<8);

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
    USART1->BRR  =  (4 << 4) | 5; // Đảm bảo tốc độ baudrate 115200
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

void convert_IntToString(uint8_t * str, uint8_t * index_str, uint32_t number){
    uint8_t index = 0;
    while (1)
    {
        str[index] = (number % 10 + 48);
        number /= 10;
        if(number == 0) break;
        index++;
    }
    *index_str = index+1;
    uint8_t temp;
    for(int i=0; i<*index_str/2;i++){
        temp = str[i];
        str[i] = str[*index_str-i-1];
        str[*index_str-i-1] = temp;
    }
}

int main() {
    uint8_t RxBuffer[50];
    uint32_t index_buffer = 50;
    usart1_Init();
    CRC_init();
    uint32_t sw = (GPIOA->IDR & (1<<8))>>8;
    uint8_t string[20];
    uint8_t index_string;
    convert_IntToString(string,&index_string,sw);
    usart_writeString(string,index_string);
    if(sw==0) jump_application(0x8001000);
    usart_writeString("\nstatus: Bootloader mode",25);
    while (1) {
        if((USART1->SR & (1<<5)) != 0){
            usart_readString(RxBuffer,&index_buffer,50);
            uint32_t crc_host  = *(uint32_t*)(RxBuffer+index_buffer-4);
            uint32_t crc_slave = CRC_caculator(RxBuffer,index_buffer-4);
            if(crc_host == crc_slave){
                uint32_t mode = *(uint32_t *)RxBuffer;
                if(mode == 1){
                    //write flash
                    uint32_t address = *(uint32_t *)(RxBuffer+4);
                    uint32_t length  = *(uint32_t *)(RxBuffer+8);
                    int8_t step = 2;
                    for (int i = 0; i < length; i+=step){
                        Flash_writeHaftword(address+i,*(uint16_t *)(RxBuffer+12+i));
                    }
                    if(length%2>0) Flash_writeByte(address+length,*(uint8_t *)(RxBuffer+12+length));
                    convert_IntToString(string,&index_string,*(uint32_t *)(RxBuffer+4));
                    usart_writeString(string,index_string);
                }
                else if(mode == 2){
                    //read flash
                }
                else if(mode == 3){
                    //reset flash
                    uint32_t address = *(uint32_t *)(RxBuffer+4);
                    uint32_t length  = 8;
                    for (int i = 0; i < length; i++){
                        Flash_eraseFlash(address+i*1024);
                    }
                    usart_writeString("status: Reset Complete",23);
                }
                else if(mode == 4){
                    usart_writeString("status: Application mode",25);
                    uint32_t address = *(uint32_t *)(RxBuffer+4);
                    jump_application(address);
                }
            }
            else{
                usart_writeString("Error CRC",10);
            }
        }
    }

    return 0;
}
