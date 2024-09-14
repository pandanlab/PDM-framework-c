/* startup.s */

/* Định nghĩa kích thước stack và con trỏ stack ban đầu */
#define SRAM_START 0x20000000
#define SRAM_SIZE  (20 * 1024)
#define SRAM_END   (SRAM_START + SRAM_SIZE)
#define STACK_START SRAM_END

/* Khai báo các biến bên ngoài */
.extern main

/* Định nghĩa phần .data và .bss */
.extern _sdata
.extern _edata
.extern _sidata
.extern _sbss
.extern _ebss

/* Phần định nghĩa bảng vectơ */
.section .isr_vector, "a", %progbits
    .word STACK_START                   /* Con trỏ stack ban đầu */
    .word Reset_Handler                 /* Reset handler */
    .word NMI_Handler                   /* NMI handler */
    .word HardFault_Handler             /* Hard Fault handler */
    .word MemManage_Handler             /* Memory Management Fault handler */
    .word BusFault_Handler              /* Bus Fault handler */
    .word UsageFault_Handler            /* Usage Fault handler */
    .word 0                             /* Dự phòng */
    .word 0                             /* Dự phòng */
    .word 0                             /* Dự phòng */
    .word 0                             /* Dự phòng */
    .word SVC_Handler                   /* SVCall handler */
    .word DebugMon_Handler              /* Debug Monitor handler */
    .word 0                             /* Dự phòng */
    .word PendSV_Handler                /* PendSV handler */
    .word SysTick_Handler               /* SysTick handler */
    .word WWDG_IRQHandler               /* Window Watchdog */
    .word PVD_IRQHandler                /* PVD qua EXTI Line detect */
    .word TAMPER_IRQHandler             /* Tamper */
    .word RTC_IRQHandler                /* RTC */
    .word FLASH_IRQHandler              /* Flash */
    .word RCC_IRQHandler                /* RCC */
    .word EXTI0_IRQHandler              /* EXTI Line 0 */
    .word EXTI1_IRQHandler              /* EXTI Line 1 */
    .word EXTI2_IRQHandler              /* EXTI Line 2 */
    .word EXTI3_IRQHandler              /* EXTI Line 3 */
    .word EXTI4_IRQHandler              /* EXTI Line 4 */
    .word DMA1_Channel1_IRQHandler      /* DMA1 Channel 1 */
    .word DMA1_Channel2_IRQHandler      /* DMA1 Channel 2 */
    .word DMA1_Channel3_IRQHandler      /* DMA1 Channel 3 */
    .word DMA1_Channel4_IRQHandler      /* DMA1 Channel 4 */
    .word DMA1_Channel5_IRQHandler      /* DMA1 Channel 5 */
    .word DMA1_Channel6_IRQHandler      /* DMA1 Channel 6 */
    .word DMA1_Channel7_IRQHandler      /* DMA1 Channel 7 */
    .word ADC1_2_IRQHandler             /* ADC1 & ADC2 */
    .word USB_HP_CAN1_TX_IRQHandler     /* USB High Priority hoặc CAN1 TX */
    .word USB_LP_CAN1_RX0_IRQHandler    /* USB Low Priority hoặc CAN1 RX0 */
    .word CAN1_RX1_IRQHandler           /* CAN1 RX1 */
    .word CAN1_SCE_IRQHandler           /* CAN1 SCE */
    .word EXTI9_5_IRQHandler            /* EXTI Line 9..5 */
    .word TIM1_BRK_IRQHandler           /* TIM1 Break */
    .word TIM1_UP_IRQHandler            /* TIM1 Update */
    .word TIM1_TRG_COM_IRQHandler       /* TIM1 Trigger and Commutation */
    .word TIM1_CC_IRQHandler            /* TIM1 Capture Compare */
    .word TIM2_IRQHandler               /* TIM2 */
    .word TIM3_IRQHandler               /* TIM3 */
    .word TIM4_IRQHandler               /* TIM4 */
    .word I2C1_EV_IRQHandler            /* I2C1 Event */
    .word I2C1_ER_IRQHandler            /* I2C1 Error */
    .word I2C2_EV_IRQHandler            /* I2C2 Event */
    .word I2C2_ER_IRQHandler            /* I2C2 Error */
    .word SPI1_IRQHandler               /* SPI1 */
    .word SPI2_IRQHandler               /* SPI2 */
    .word USART1_IRQHandler             /* USART1 */
    .word USART2_IRQHandler             /* USART2 */
    .word USART3_IRQHandler             /* USART3 */
    .word EXTI15_10_IRQHandler          /* EXTI Line 15..10 */
    .word RTCAlarm_IRQHandler           /* RTC Alarm qua EXTI Line */
    .word USBWakeUp_IRQHandler          /* USB Wakeup từ chế độ ngủ */
    .word TIM8_BRK_IRQHandler           /* TIM8 Break */
    .word TIM8_UP_IRQHandler            /* TIM8 Update */
    .word TIM8_TRG_COM_IRQHandler       /* TIM8 Trigger and Commutation */
    .word TIM8_CC_IRQHandler            /* TIM8 Capture Compare */
    .word ADC3_IRQHandler               /* ADC3 */
    .word FSMC_IRQHandler               /* FSMC */
    .word SDIO_IRQHandler               /* SDIO */
    .word TIM5_IRQHandler               /* TIM5 */
    .word SPI3_IRQHandler               /* SPI3 */
    .word UART4_IRQHandler              /* UART4 */
    .word UART5_IRQHandler              /* UART5 */
    .word TIM6_IRQHandler               /* TIM6 */
    .word TIM7_IRQHandler               /* TIM7 */
    .word DMA2_Channel1_IRQHandler      /* DMA2 Channel 1 */
    .word DMA2_Channel2_IRQHandler      /* DMA2 Channel 2 */
    .word DMA2_Channel3_IRQHandler      /* DMA2 Channel 3 */
    .word DMA2_Channel4_5_IRQHandler    /* DMA2 Channel 4 và Channel 5 */
    .word DMA2_Channel5_IRQHandler      /* DMA2 Channel 5 */

/* Xử lý ngắt mặc định */
.section .text
Default_Handler:
    b Default_Handler

/* Xử lý ngắt Reset */
.section .text
Reset_Handler:
    /* Khởi tạo con trỏ stack */
    ldr sp, =STACK_START
    
    /* Khởi tạo phần .data */
    ldr r0, =_sdata
    ldr r1, =_edata
    ldr r2, =_sidata
    b LoopCopyDataInit

LoopCopyDataInit:
    cmp r0, r1
    bge LoopBssInit
    ldr r3, [r2], #4
    str r3, [r0], #4
    b LoopCopyDataInit

LoopBssInit:
    /* Khởi tạo phần .bss */
    ldr r0, =_sbss
    ldr r1, =_ebss
    mov r2, #0
    b LoopBssZero

LoopBssZero:
    cmp r0, r1
    bge Main
    str r2, [r0], #4
    b LoopBssZero

Main:
    bl main
    b Main
