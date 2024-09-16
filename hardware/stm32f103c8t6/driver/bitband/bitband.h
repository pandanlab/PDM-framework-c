#if !defined(BITBAND_H)
#define BITBAND_H

#include<stdint.h>
#define BITBAND_PERIPHERAL_REGION       0x40000000
#define BITBAND_PERIPHERAL_ALIAS        0x42000000
#define BITBAND_SRAM_REGION             0x20000000
#define BITBAND_SRAM_ALIAS              0x22000000

volatile uint32_t bitband_peripheral(volatile uint32_t address_input);
volatile uint32_t bitband_peripheral_index(volatile uint32_t address_input, uint32_t index);

volatile uint32_t bitband_sram(volatile uint32_t address_input);
volatile uint32_t bitband_sram_index(volatile uint32_t address_input, uint32_t index);

#endif // BITBAND_H
