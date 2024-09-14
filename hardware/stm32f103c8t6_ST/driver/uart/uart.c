#include "uart.h"

// Khởi tạo UART1 với baud rate 9600
void UART_Init(void) {
    uint32_t usartdiv;
    uint32_t F_mass, F_Frac;

    // Kích hoạt đồng hồ cho GPIOA và UART1
    rcc_apb2_enable(APB2_GPIOA);
    rcc_apb2_enable(APB2_USART1);

    // Cấu hình chân TX (PA9) và RX (PA10) cho UART
    pinMode(GPIOA, PIN_9, OUTPUT, ALTERNATE_PUSHPULL_OUTPUT); // PA9 - TX, Alternate Function Push-Pull
    pinMode(GPIOA, PIN_10, INPUT, FLOAT_INPUT); // PA10 - RX, Floating Input

    // Cấu hình UART1
    UART1->CR1 &= ~(USART_CR1_M | USART_CR1_PCE | USART_CR1_PS); // Clear previous settings

    // Bật truyền dữ liệu (TE) và nhận dữ liệu (RE)
    UART1->CR1 |= (USART_CR1_TE | USART_CR1_RE);

    // Tính toán baud rate
    usartdiv = (25 * 16000000) / (4 * 9600);
    F_mass   = usartdiv / 100;
    F_Frac   = usartdiv - (F_mass * 100);
    F_Frac   = (((F_Frac * 16) + 50) / 100) & 0x0F;

    // Cài đặt baud rate
    UART1->BRR = (F_mass << 4) | F_Frac;

    // Bật UART1
    UART1->CR1 |= USART_CR1_UE; // Enable UART
}

// Gửi dữ liệu qua UART1
void UART_SendData(uint8_t * pTXBuffer, uint32_t len) {
    for (uint32_t i = 0; i < len; i++) {
        // Đợi cho đến khi thanh ghi dữ liệu truyền ra rỗng
        while (!(UART1->SR & USART_SR_TXE));
        // Ghi dữ liệu vào thanh ghi dữ liệu
        UART1->DR = pTXBuffer[i];
    }
}

// Nhận dữ liệu từ UART1
void UART_ReceiveData(uint8_t * pRXBuffer, uint32_t len) {
    for (uint32_t i = 0; i < len; i++) {
        // Đợi cho đến khi có dữ liệu trong thanh ghi dữ liệu nhận
        while (!(UART1->SR & USART_SR_RXNE));
        // Đọc dữ liệu từ thanh ghi dữ liệu
        pRXBuffer[i] = UART1->DR;
    }
}
