#include "unit_led.h"

//PA8

void configureLed(){
    rcc_apb2_enable(APB2_GPIOA);
    pinMode(GPIOA,8,OUTPUT,GENERAL_PUSHPULL_OUTPUT);
}

void onLed(){
    digitalWritePin(GPIOA,8,0);
}
void offLed(){
    digitalWritePin(GPIOA,8,1);
}
