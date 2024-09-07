#include"unit_pc13.h"

void pc13_config(){
    enable_gpio();
    config_gpioC();
}

void pc13_on(){
    led_on();
}

void pc13_off(){
    led_off();
}