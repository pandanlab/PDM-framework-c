#if !defined(rcc_h)
#define rcc_h

#include <stdint.h>

// Cấu trúc thanh ghi RCC cho STM32F103C8T6
typedef struct
{
    volatile uint32_t CR;       // Clock control register
    volatile uint32_t CFGR;     // Clock configuration register
    volatile uint32_t CIR;      // Clock interrupt register
    volatile uint32_t APB2RSTR; // APB2 peripheral reset register
    volatile uint32_t APB1RSTR; // APB1 peripheral reset register
    volatile uint32_t AHBENR;   // AHB peripheral clock enable register
    volatile uint32_t APB2ENR;  // APB2 peripheral clock enable register
    volatile uint32_t APB1ENR;  // APB1 peripheral clock enable register
    volatile uint32_t BDCR;     // Backup domain control register
    volatile uint32_t CSR;      // Control/status register
} RCC_Types;

#define RCC_BASEADDR 0x40021000
#define RCC ((RCC_Types *)RCC_BASEADDR)

#define AHB_DMA1 0
#define AHB_DMA2 1
#define AHB_FLITF 4
#define AHB_CRC 6
#define AHB_FSMC 8
#define AHB_SDIO 10

#define APB2_AFIO 0
#define APB2_GPIOA 2
#define APB2_GPIOB 3
#define APB2_GPIOC 4
#define APB2_GPIOD 5
#define APB2_GPIOE 6
#define APB2_GPIOF 7
#define APB2_GPIOG 8
#define APB2_ADC1 9
#define APB2_ADC2 10
#define APB2_TIM1 11
#define APB2_SPI1 12
#define APB2_TIM8 13
#define APB2_USART1 14
#define APB2_ADC3 15
#define APB2_TIM9 19
#define APB2_TIM10 20
#define APB2_TIM11 21

#define APB1_TIM2 0
#define APB1_TIM3 1
#define APB1_TIM4 2
#define APB1_TIM5 3
#define APB1_TIM6 4
#define APB1_TIM7 5
#define APB1_TIM12 6
#define APB1_TIM13 7
#define APB1_TIM14 8
#define APB1_WWDG 11
#define APB1_SPI2 14
#define APB1_SPI3 15
#define APB1_USART2 17
#define APB1_USART3 18
#define APB1_USART4 19
#define APB1_USART5 20
#define APB1_I2C1 21
#define APB1_I2C2 22
#define APB1_USB 23
#define APB1_CAN 25
#define APB1_BKP 27
#define APB1_PWR 28
#define APB1_DAC 29

void rcc_ahb_enable(uint8_t peripheral);
void rcc_apb2_enable(uint8_t peripheral);
void rcc_apb1_enable(uint8_t peripheral);

#endif // rcc_h
