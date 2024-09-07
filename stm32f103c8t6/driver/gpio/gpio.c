#include "gpio.h"

uint32_t *pt;

void enable_gpio(){
    // Enable clock for GPIOA and GPIOC
    uint32_t *pt = (uint32_t*)addr_register_rcc_apb2;
    *pt |= (1 << 2);  // Enable GPIOA clock
    *pt |= (1 << 4);  // Enable GPIOC clock
}

void config_gpioA(){
    pt = (uint32_t*)addr_register_gpioa_configuration_low;
    *pt &= ~(0xF);    // Clear bits 0-3
    *pt |= (0x8);     // Set MODE0 to 10: Input mode with pull-up/down
}
void config_gpioC(){
    // Configure PC13 as output, push-pull, 10MHz
    pt = (uint32_t*)addr_register_gpioc_configuration_high;
    *pt &= ~(0xF << 20);  // Clear bits 20-23
    *pt |= (0x1 << 20);   // Set MODE13 to 01: Output mode, max speed 10MHz
}


void led_on(){
    pt = (uint32_t*)addr_register_gpioc_output_data;
    *pt |=(1<<13);
}

void led_off(){
    pt = (uint32_t*)addr_register_gpioc_output_data;
    *pt &=~(1<<13);
}