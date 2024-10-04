#include "../../../hardware/stm32f103c8t6/driver/gpio/gpio.h"
#include "../../../hardware/stm32f103c8t6/driver/rcc/rcc.h"
#include "../../../hardware/stm32f103c8t6/driver/flash/flash.h"
#include "../../../software/layer_unit/unit_delay/unit_delay.h"

int main(){
    //LATENCY Selector
    FLASH->ACR &= ~(1<<0);
    FLASH->ACR |=  (1<<1);
    FLASH->ACR &= ~(1<<2);

    //Seclect HSE
    RCC->CR |= (1<<0);

    //configure PLLSRC
    RCC->CFGR |= (1<<16);

    //select PLL x9 => MUL = 0111 (7)
    RCC->CFGR &= ~(1<<18);
    RCC->CFGR |= ~(1<<19);
    RCC->CFGR &=  (1<<20);
    RCC->CFGR &= ~(1<<21);

    //on PLL
    RCC->CR |=(1<<24);

    //select SW
    RCC->CFGR |= (1<<1);
    RCC->CFGR &= ~(1<<0);

    // while (!(((RCC->CFGR & (1<<2))>>2) & (RCC->CFGR & (1<<3)==0)));

    //select MCO
    RCC->CFGR &= ~(1<<24);
    RCC->CFGR &= ~(1<<25);
    RCC->CFGR |= (1<<26);

    //Clock GPIOA,GPIOC
    RCC->APB2ENR |= (1<<2);
    RCC->APB2ENR |= (1<<4);

    //PA8 output/alternate pushpull
    GPIOA->CRH |= (1<<0);
    GPIOA->CRH |= (1<<1);
    GPIOA->CRH &= ~(1<<2);
    GPIOA->CRH |= (1<<3);

    GPIOC->CRH |= (1<<20);
    GPIOC->CRH &= ~(1<<21);
    GPIOC->CRH &= ~(1<<22);
    GPIOC->CRH |= (1<<23);

    while (1)
    {
        GPIOC->ODR = !(GPIOC->ODR);
        delay(1000);
    }

    return 0;
}