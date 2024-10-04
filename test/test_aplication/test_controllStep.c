#include "../hardware/stm32f103rct6/driver/rcc/rcc.h"
#include "../hardware/stm32f103rct6/driver/gpio/gpio.h"
#include "../hardware/stm32f103rct6/driver/timer/timer.h"
#include "../hardware/stm32f103rct6/driver/nvic/nvic.h"
#include "../software/layer_unit/unit_delay/unit_delay.h"

// Global variables for pulse counting
int8_t sw = 0;
uint32_t pulse_count = 0;
const uint32_t target_pulses = 64000;

// Timer initialization function
void Timer1_init(void) {
    // Enable clock for Timer 1
    rcc_apb2_enable(APB2_TIM1);

    // Configure timer
    TIM1->TIMx_PSC = 0; // No prescaler (timer clock = 8 MHz)
    TIM1->TIMx_ARR = 143; // Auto-reload value for desired frequency

    // Enable counter
    TIM1->TIMx_CR1 = 0; // Reset control register
    TIM1->TIMx_CR1 |= (1 << 0); // Enable the counter
    TIM1->TIMx_EGR |= (1 << 0); // Trigger update event

    // Enable update interrupt
    TIM1->TIMx_DIER |= (1 << 0); // Enable update interrupt

    // Enable Timer 1 interrupt in NVIC
    NVIC_EnableIRQ(25); // Enable Timer 1 interrupt
}

// Motor initialization function
void Motor_init(void) {
    // Enable clock for GPIOA
    rcc_apb2_enable(APB2_GPIOA);

    // Configure GPIO pins
    pinMode(GPIOA, PIN_0, OUTPUT, GENERAL_PUSHPULL_OUTPUT); // Enable pin
    pinMode(GPIOA, PIN_1, OUTPUT, GENERAL_PUSHPULL_OUTPUT); // STEP pin
    pinMode(GPIOA, PIN_2, OUTPUT, GENERAL_PUSHPULL_OUTPUT); // DIR pin

    // Initial state
    digitalWritePin(GPIOA, PIN_0, 0); // Disable motor initially
    digitalWritePin(GPIOA, PIN_2, 1); // Set direction (1 or 0 as needed)
}

// Timer interrupt handler
void TIM1_UP_IRQHandler(void) {
    if (TIM1->TIMx_SR & (1 << 0)) {
        if(sw==0){
            GPIOA->ODR ^= (1 << 1);
            if(pulse_count >= target_pulses) sw=1;
            pulse_count++;
        }
        TIM1->TIMx_SR &= ~(1 << 0);
    }
}

int main(void) {
    Timer1_init(); // Initialize timer
    Motor_init();  // Initialize motor control

    while (1) {
        if(sw == 1){
            delay(500);
            pulse_count = 0; // Reset pulse count
            GPIOA->ODR ^= (1 << 2);
            GPIOA->ODR &= ~(1 << 0);
            sw = 0;
        }

    }

    return 0; // Main should return an int
}
