#include<stdint.h>
#include "time.h"

void delay(int milliseconds) {
    for (volatile uint32_t i = 0; i < (milliseconds*1000); i++);
}