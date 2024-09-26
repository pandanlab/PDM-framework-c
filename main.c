#include "hardware/stm32f103c8t6/driver/gpio/gpio.h"
#include "hardware/stm32f103c8t6/driver/rcc/rcc.h"

void delay(volatile uint32_t ms){
    for(volatile uint32_t i = 0; i < (ms*1000);i++);
}

int main(){
    rcc_apb2_enable(APB2_GPIOC);
    pinMode(GPIOC,PIN_13,OUTPUT,GENERAL_PUSHPULL_OUTPUT);

    while (1)
    {
        digitalWritePin(GPIOC,PIN_13,HIGH);
        delay(100);
        digitalWritePin(GPIOC,PIN_13,LOW);
        delay(100);
    }
    
    return 0;
}