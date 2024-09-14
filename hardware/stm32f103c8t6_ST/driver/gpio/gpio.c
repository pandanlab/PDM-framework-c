#include "gpio.h"

void pinMode(GPIO_Types *gpio, uint8_t pin, uint8_t mode, uint8_t cnf) {
    uint8_t position = pin *4;
    if(pin<8) gpio->CRL = (gpio->CRL & ~(0x0F << position)) | ((mode | (cnf << 2)) << position);
    else gpio->CRH = (gpio->CRH & ~(0x0F << position)) | ((mode | (cnf << 2)) << position);
}

void digitalWritePin(GPIO_Types *gpio, uint8_t pin, uint8_t value) {
    if (value) {
        gpio->ODR |= (1 << pin);
    } else {
        gpio->ODR &= ~(1 << pin);
    }
}

void digitalWritePort(GPIO_Types *gpio, uint16_t value){
    gpio->ODR = (uint32_t)value;
}

void digitalReadPin(GPIO_Types *gpio, uint8_t pin);
void analogWritePin(GPIO_Types *gpio, uint8_t pin, uint8_t value);
void analogReadPin(GPIO_Types *gpio, uint8_t pin);