#include "nvic.h"

void NVIC_EnableIRQ(uint8_t IRQn) {
    NVIC->ISER[IRQn / 32] = (1 << (IRQn % 32));
}
