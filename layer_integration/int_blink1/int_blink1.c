#include "int_blink1.h"

void blink_config(){
    pc13_config();
}

void blink_led(){
    pc13_on();
    delay(1000);
    pc13_off();
    delay(1000);
}