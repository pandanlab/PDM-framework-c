#include "../../hardware/stm32f103c8t6/driver/gpio/gpio.h"
#include "../../hardware/stm32f103c8t6/driver/rcc/rcc.h"
#include "../../software/layer_unit/unit_delay/unit_delay.h"

int main(){
    //bat xung clock cho gpio
    rcc_apb2_enable(APB2_GPIOC);

    //cau hinh chan 13
    pinMode(GPIOC,PIN_13,OUTPUT,GENERAL_PUSHPULL_OUTPUT);

    while(1){
        digitalWritePin(GPIOC,PIN_13,LOW);
        delay(100);
        digitalWritePin(GPIOC,PIN_13,HIGH);
        delay(100);
    }

    return 0;
}