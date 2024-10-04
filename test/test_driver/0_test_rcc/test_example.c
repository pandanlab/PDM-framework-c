#include "../../../hardware/stm32f103c8t6/driver/gpio/gpio.h"
#include "../../../hardware/stm32f103c8t6/driver/rcc/rcc.h"
#include "../../../hardware/stm32f103c8t6/driver/flash/flash.h"
#include "../../../software/layer_unit/unit_delay/unit_delay.h"

int main() {
    // LATENCY Selector
    FLASH->ACR &= ~(1<<0);
    FLASH->ACR |=  (1<<1);
    FLASH->ACR &= ~(1<<2);

    // Select HSE
    RCC->CR |= (1<<0); // Enable HSE
    delay(5000); // Wait for HSE to stabilize

    // Configure PLLSRC
    RCC->CFGR |= (1<<16); // Select HSE as PLL source

    // Select PLL x9 (MUL = 1001 = 9)
    RCC->CFGR |= (1<<18) | (1<<19) | (1<<20); // Set PLL multiplication factor
    RCC->CFGR &= ~(1<<21); // Ensure the 21st bit is 0

    // Enable PLL
    RCC->CR |= (1<<24); // Set PLLON

    // Select PLL as system clock
    RCC->CFGR |= (1<<1); // Set SW to 10 (PLL selected)
    RCC->CFGR &= ~(1<<0); // Ensure SW is set to PLL

    delay(5000); // Wait for PLL to stabilize

    // Select MCO to output system clock on PA8
    RCC->CFGR &= ~(1<<24); // Clear MCO bits
    RCC->CFGR &= ~(1<<25); 
    RCC->CFGR |= (1<<26); // Set MCO to system clock

    // Enable clock for GPIOA and GPIOC
    RCC->APB2ENR |= (1<<2); // Enable GPIOA clock
    RCC->APB2ENR |= (1<<4); // Enable GPIOC clock

    // PA8 output/alternate push-pull
    GPIOA->CRH &= ~(0xF); // Clear PA8 settings
    GPIOA->CRH |= (0xB); // Set PA8 to alternate function push-pull

    // Configure PC13 (or another pin) as output push-pull
    GPIOC->CRH &= ~(0xF << 20); // Clear PC13 settings
    GPIOC->CRH |= (0x2 << 20); // Set PC13 to output push-pull

    while (1) {
        GPIOC->ODR ^= (1 << 13); // Toggle PC13 (or PA8 if you want)
        delay(1000); // Delay
    }

    return 0; // Not generally reached in embedded systems
}
