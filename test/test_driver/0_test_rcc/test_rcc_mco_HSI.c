#include "../../../hardware/stm32f103c8t6/driver/gpio/gpio.h"
#include "../../../hardware/stm32f103c8t6/driver/rcc/rcc.h"

int main(){
    //select MCO
    RCC->CFGR |= (1<<24);
    RCC->CFGR &= ~(1<<25);
    RCC->CFGR |= (1<<26);

    //Clock GPIOA
    RCC->APB2ENR |= (1<<2);

    //PA8 output/alternate pushpull
    GPIOA->CRH |= (1<<0);
    GPIOA->CRH &= ~(1<<1);
    GPIOA->CRH &= ~(1<<2);
    GPIOA->CRH |= (1<<3);

    while (1)
    {
        /* code */
    }
    


    return 0;
}