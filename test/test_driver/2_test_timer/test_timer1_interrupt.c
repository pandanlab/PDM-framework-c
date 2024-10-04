#include "../../../hardware/stm32f103rct6/driver/rcc/rcc.h"
#include "../../../hardware/stm32f103rct6/driver/gpio/gpio.h"
#include "../../../hardware/stm32f103rct6/driver/timer/timer.h"
#include "../../../hardware/stm32f103rct6/driver/nvic/nvic.h"

void Timer1_init(void){
    RCC->APB2ENR |= (1<<11);  //Bat xung clock TIMER 1
    RCC->APB2ENR |= (1<<4);

    GPIOC->CRH |= (1<<20);
    GPIOC->CRH &= ~(1<<21);
    GPIOC->CRH &= ~(1<<22);
    GPIOC->CRH &= ~(1<<23);

    //cau hinh timer
    TIM1->TIMx_PSC = 79;
    TIM1->TIMx_ARR = 999;

    //cau hinh dem tang
    TIM1->TIMx_CR1 = 0;
    TIM1->TIMx_CR1 |= (1<<0); // Counter enable
    TIM1->TIMx_EGR |= (1<<0); // Gửi sự kiện cập nhật

    // Kích hoạt ngắt
    TIM1->TIMx_DIER |= (1 << 0); // Kích hoạt ngắt cập nhật

    //cau hinh ngat
    NVIC_EnableIRQ(25); // Kích hoạt ngắt Timer 1
}

// Hàm xử lý ngắt
void TIM1_UP_IRQHandler(void) {
    if (TIM1->TIMx_SR & (1 << 0)) { // Kiểm tra ngắt cập nhật
        TIM1->TIMx_SR &= ~(1 << 0); // Xóa cờ ngắt
        GPIOC->ODR ^= (1 << 13); // Đổi trạng thái PC13
    }
}

int main(){
    Timer1_init();
    while (1)
    {

    }

}