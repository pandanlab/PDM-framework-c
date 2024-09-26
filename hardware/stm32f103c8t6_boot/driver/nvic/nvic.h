#if !defined(NVIC_H)
#define NVIC_H

#include <stdint.h>

typedef struct {
    volatile uint32_t ISER[3];   // 0x00: Interrupt Set-Enable Register
    // Bạn có thể thêm các phần khác nếu cần
} NVIC_Type;

#define NVIC ((NVIC_Type *)0xE000E100)  // Địa chỉ NVIC
void NVIC_EnableIRQ(uint8_t IRQn);

#endif // NVIC_H
