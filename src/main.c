#include <stdint.h>
#include "../hardware/stm32f103c8t6/driver/bitband/bitband.h"

#define  RCC_BASEADDR                  0x40021000
#define  RCC_ABP2ENR                   (RCC_BASEADDR + 0x18)

#define  GPIOC_BASEADDR                0x40011000
#define  GPIOC_CFH                     (GPIOC_BASEADDR + 0x04)
#define  GPIOC_ODR                     (GPIOC_BASEADDR + 0x0C)

void delay(volatile uint32_t time){
  for (volatile uint32_t i = 0; i < (time*1000); i++);
}

int main(void)
{
	uint32_t *pt;
	pt = (uint32_t*)bitband_peripheral_index(RCC_ABP2ENR,4);
	*pt = 1;

	pt = (uint32_t*)bitband_peripheral(GPIOC_CFH);
	*(pt+20)=1;
	*(pt+21)=0;
	*(pt+22)=0;
	*(pt+23)=0;
	
	pt = (uint32_t*)bitband_peripheral_index(GPIOC_ODR,13);

	while(1){
		*pt = 1;
		delay(1000);
		*pt = 0;
		delay(1000);
	}

}
