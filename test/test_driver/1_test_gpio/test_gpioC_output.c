//blink led chan pc13
#include <stdint.h>
#include "../../../hardware/stm32f103c8t6/driver/bitband/bitband.h"

#define RCC_BASEADDR                 0x40021000
#define RCC_APB2ENR                  (RCC_BASEADDR + 0x18)

#define GPIOC_BASEADDR               0x40011000
#define GPIOC_CRH                    (GPIOC_BASEADDR + 0x04)
#define GPIOC_ODR                    (GPIOC_BASEADDR + 0x0C)

int main(void){
	//tao con tro
	uint32_t *pt;
	
	//bat xung clock cho gpioc
	pt = (uint32_t *) bitband_peripheral(RCC_APB2ENR);
	*(pt+4) = 1; //bat gia tri 1 o bit thu 4
	
	//cau hinh chan cho gpioc (c13)
	pt = (uint32_t *) bitband_peripheral(GPIOC_CRH);
	//mode = 01 => cau hinh output 10mhz
	*(pt+20) = 1;
	*(pt+21) = 0;
	*(pt+22) = 0;
	*(pt+23) = 0;
	
	pt = (uint32_t *) bitband_peripheral(GPIOC_ODR);
	
	while(1){
		*(pt+13) = 0;
		*(pt+13) = 1;
	}
	return 0;
}