#if !defined(gpio_h)
#define gpio_h

#include <stdint.h>

typedef struct
{
	volatile uint32_t CRL;
	volatile uint32_t CRH;
	volatile uint32_t IDR;
	volatile uint32_t ODR;
	volatile uint32_t BSRR;
	volatile uint32_t BSR;
	volatile uint32_t LCKR;
} GPIO_Types;

#define GPIOA_BASEADDR 0x40010800
#define GPIOB_BASEADDR 0x40010C00
#define GPIOC_BASEADDR 0x40011000
#define GPIOD_BASEADDR 0x40011400
#define GPIOE_BASEADDR 0x40011800
#define GPIOF_BASEADDR 0x40011C00
#define GPIOG_BASEADDR 0x40012000

#define GPIOA ((GPIO_Types *)GPIOA_BASEADDR)
#define GPIOB ((GPIO_Types *)GPIOB_BASEADDR)
#define GPIOC ((GPIO_Types *)GPIOC_BASEADDR)
#define GPIOD ((GPIO_Types *)GPIOD_BASEADDR)
#define GPIOE ((GPIO_Types *)GPIOE_BASEADDR)
#define GPIOF ((GPIO_Types *)GPIOF_BASEADDR)
#define GPIOG ((GPIO_Types *)GPIOG_BASEADDR)

#define PIN_0 0
#define PIN_1 1
#define PIN_2 2
#define PIN_3 3
#define PIN_4 4
#define PIN_5 5
#define PIN_6 6
#define PIN_7 7
#define PIN_8 8
#define PIN_9 9
#define PIN_10 10
#define PIN_11 11
#define PIN_12 12
#define PIN_13 13
#define PIN_14 14
#define PIN_15 15

#define INPUT 0
#define OUTPUT 1
#define OUTPUT_LOW 2
#define OUTPUT_HIGH 3

#define ANALOG_INPUT 0
#define FLOAT_INPUT 1
#define PULL_INPUT 2

#define GENERAL_PUSHPULL_OUTPUT 0
#define GENERAL_OPENDRAIN_OUTPUT 1
#define ALTERNATE_PUSHPULL_OUTPUT 2
#define ALTERNATE_OPENDRAIN_OUTPUT 3

#define HIGH 1
#define LOW 0

void pinMode(GPIO_Types *gpio, uint8_t pin, uint8_t mode, uint8_t configure);
void digitalWritePin(GPIO_Types *gpio, uint8_t pin, uint8_t value);
void digitalWritePort(GPIO_Types *gpio, uint16_t value);
void digitalReadPin(GPIO_Types *gpio, uint8_t pin);
void analogWritePin(GPIO_Types *gpio, uint8_t pin, uint8_t value);
void analogReadPin(GPIO_Types *gpio, uint8_t pin);

#endif // gpio_h
