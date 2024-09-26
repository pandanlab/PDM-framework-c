#if !defined(TIMER_H)
#define TIMER_H

#include<stdint.h>

typedef struct
{
	volatile uint32_t TIMx_CR1;
	volatile uint32_t TIMx_CR2;
	volatile uint32_t TIMx_SMCR;
	volatile uint32_t TIMx_DIER;
	volatile uint32_t TIMx_SR;
	volatile uint32_t TIMx_EGR;
	volatile uint32_t TIMx_CCMR1;
	volatile uint32_t TIMx_CCMR2;
	volatile uint32_t TIMx_CCER;
	volatile uint32_t TIMx_CNT;
	volatile uint32_t TIMx_PSC;
	volatile uint32_t TIMx_ARR;
	volatile uint32_t TIMx_RCR;
	volatile uint32_t TIMx_CCR1;
	volatile uint32_t TIMx_CCR2;
	volatile uint32_t TIMx_CCR3;
	volatile uint32_t TIMx_CCR4;
	volatile uint32_t TIMx_BDTR;
	volatile uint32_t TIMx_DCR;
	volatile uint32_t TIMx_DMAR;
} AdvancedControlTimer_Types;  //TIM1 and TIM8

typedef struct
{
	volatile uint32_t TIMx_CR1;
	volatile uint32_t TIMx_CR2;
	volatile uint32_t TIMx_SMCR;
	volatile uint32_t TIMx_DIER;
	volatile uint32_t TIMx_SR;
	volatile uint32_t TIMx_EGR;
	volatile uint32_t TIMx_CCMR1;
	volatile uint32_t TIMx_CCMR2;
	volatile uint32_t TIMx_CCER;
	volatile uint32_t TIMx_CNT;
	volatile uint32_t TIMx_PSC;
	volatile uint32_t TIMx_ARR;
	volatile uint32_t Reserved1;
	volatile uint32_t TIMx_CCR1;
	volatile uint32_t TIMx_CCR2;
	volatile uint32_t TIMx_CCR3;
	volatile uint32_t TIMx_CCR4;
	volatile uint32_t Reserved2;
	volatile uint32_t TIMx_DCR;
	volatile uint32_t TIMx_DMAR;
} GeneralPurposeTimer1_Types; ///TIM2 -> TIM5/


typedef struct
{
	volatile uint32_t TIMx_CR1;             
	volatile uint32_t TIMx_SMCR;
	volatile uint32_t TIMx_DIER;
	volatile uint32_t TIMx_SR;
	volatile uint32_t TIMx_EGR;
	volatile uint32_t TIMx_CCMR1;
	volatile uint32_t Reserved1;
	volatile uint32_t TIMx_CCER;
	volatile uint32_t TIMx_CNT;
	volatile uint32_t TIMx_PSC;
	volatile uint32_t TIMx_ARR;
	volatile uint32_t Reserved2;
	volatile uint32_t TIMx_CCR1;
	volatile uint32_t TIMx_CCR2;
} GeneralPurposeTimer2_Types; //TIM9 and TIM12/

typedef struct
{
	volatile uint32_t TIMx_CR1;
	volatile uint32_t TIMx_SMCR;
	volatile uint32_t TIMx_DIER;
	volatile uint32_t TIMx_SR;
	volatile uint32_t TIMx_EGR;
	volatile uint32_t TIMx_CCMR1;
	volatile uint32_t Reserved1;
	volatile uint32_t TIMx_CCER;
	volatile uint32_t TIMx_CNT;
	volatile uint32_t TIMx_PSC;
	volatile uint32_t TIMx_ARR;
	volatile uint32_t Reserved2;
	volatile uint32_t TIMx_CCR1;
} GeneralPurposeTimer3_Types; //TIM10,11,13,14/


typedef struct
{
	volatile uint32_t TIMx_CR1;
	volatile uint32_t TIMx_CR2;
    volatile uint32_t Reserved1;
	volatile uint32_t TIMx_DIER;
	volatile uint32_t TIMx_SR;
	volatile uint32_t TIMx_EGR;
	volatile uint32_t Reserved2;
	volatile uint32_t Reserved3;
    volatile uint32_t Reserved4;
	volatile uint32_t TIMx_CNT;
	volatile uint32_t TIMx_PSC;
	volatile uint32_t TIMx_ARR;
} BasicTimer_Types; //TIM6, TIM7/

#define TIM1_BASEADDR                0x40012C00
#define TIM2_BASEADDR                0x40000000
#define TIM3_BASEADDR                0x40000400
#define TIM4_BASEADDR                0x40000800
#define TIM5_BASEADDR                0x40000C00
#define TIM6_BASEADDR                0x40001000
#define TIM7_BASEADDR                0x40001400
#define TIM8_BASEADDR                0x40013400
#define TIM9_BASEADDR                0x40014C00
#define TIM10_BASEADDR               0x40015000
#define TIM11_BASEADDR               0x40015400
#define TIM12_BASEADDR               0x40001800
#define TIM13_BASEADDR               0x40001C00
#define TIM14_BASEADDR               0x40002000

#define TIM1                         ((AdvancedControlTimer_Types*)TIM1_BASEADDR) 
#define TIM8                         ((AdvancedControlTimer_Types*)TIM8_BASEADDR) 

#define TIM2                         ((GeneralPurposeTimer1_Types*)TIM2_BASEADDR)
#define TIM3                         ((GeneralPurposeTimer1_Types*)TIM3_BASEADDR)
#define TIM4                         ((GeneralPurposeTimer1_Types*)TIM4_BASEADDR)
#define TIM5                         ((GeneralPurposeTimer1_Types*)TIM5_BASEADDR)

#define TIM9                         ((GeneralPurposeTimer2_Types*)TIM9_BASEADDR)
#define TIM12                        ((GeneralPurposeTimer2_Types*)TIM12_BASEADDR)

#define TIM10                        ((GeneralPurposeTimer3_Types*)TIM10_BASEADDR)
#define TIM11                        ((GeneralPurposeTimer3_Types*)TIM11_BASEADDR)
#define TIM13                        ((GeneralPurposeTimer3_Types*)TIM13_BASEADDR)
#define TIM14                        ((GeneralPurposeTimer3_Types*)TIM14_BASEADDR)

#define TIM6                         ((BasicTimer_Types*)TIM6_BASEADDR)
#define TIM7                         ((BasicTimer_Types*)TIM7_BASEADDR)

#endif // TIMER_H
