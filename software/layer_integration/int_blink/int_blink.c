#include "int_blink.h"

void configBlink(){
    configureLed();
}

void executionBlink(){
    onLed();
    delay(100);
    offLed();
    delay(100);
}