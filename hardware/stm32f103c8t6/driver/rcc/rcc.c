#include "rcc.h"

void rcc_ahb_enable(uint8_t peripheral){
    RCC->AHBENR |= (1 << peripheral);
}

void rcc_apb2_enable(uint8_t peripheral){
    RCC->APB2ENR |= (1 << peripheral);
}
void rcc_apb1_enable(uint8_t peripheral){
    RCC->APB1ENR |= (1 << peripheral);
}
