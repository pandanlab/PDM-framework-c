#include<stdint.h>

#define addr_peripheral_rcc                     0x40021000UL
#define addr_register_rcc_apb2                  (addr_peripheral_rcc + 0x18)

#define addr_peripheral_gpioa                   0x40010800UL
#define addr_register_gpioa_configuration_low   (addr_peripheral_gpioa + 0x00)  // Use GPIOA_CRL for PA0 configuration
#define addr_register_gpioa_input_data          (addr_peripheral_gpioa + 0x08)  // GPIOA IDR register

#define addr_peripheral_gpioc                   0x40011000UL
#define addr_register_gpioc_configuration_high  (addr_peripheral_gpioc + 0x04) // GPIOC CRH for PC13 configuration
#define addr_register_gpioc_output_data         (addr_peripheral_gpioc + 0x0C) // GPIOC ODR register

void enable_gpio();
void config_gpioA();
void config_gpioC();
void led_on();
void led_off();