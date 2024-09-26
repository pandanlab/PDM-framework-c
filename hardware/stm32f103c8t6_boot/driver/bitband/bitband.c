#include "bitband.h"

volatile uint32_t bitband_peripheral(volatile uint32_t address_input){
    return (BITBAND_PERIPHERAL_ALIAS + ((address_input - BITBAND_PERIPHERAL_REGION)*32));
}

volatile uint32_t bitband_peripheral_index(volatile uint32_t address_input, uint32_t index){
    return (BITBAND_PERIPHERAL_ALIAS + ((address_input - BITBAND_PERIPHERAL_REGION)*32) + (index*4));
}

volatile uint32_t bitband_sram(volatile uint32_t address_input){
    return (BITBAND_SRAM_ALIAS + ((address_input - BITBAND_SRAM_REGION)*32));
}

volatile uint32_t bitband_sram_index(volatile uint32_t address_input, uint32_t index){
    return (BITBAND_SRAM_ALIAS + ((address_input - BITBAND_SRAM_REGION)*32) + (index * 4));
}