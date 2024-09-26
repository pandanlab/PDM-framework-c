#if !defined(DMA_H)
#define DMA_H

#include <stdint.h>

typedef struct
{
    volatile uint32_t DMA_ISR;
    volatile uint32_t DMA_IFCR;

    volatile uint32_t CCR1;
    volatile uint32_t CNDTR1;
    volatile uint32_t CPAR1;
    volatile uint32_t CMAR1;
    volatile uint32_t reserved1;

    volatile uint32_t CCR2;
    volatile uint32_t CNDTR2;
    volatile uint32_t CPAR2;
    volatile uint32_t CMAR2;
    volatile uint32_t reserved2;

    volatile uint32_t CCR3;
    volatile uint32_t CNDTR3;
    volatile uint32_t CPAR3;
    volatile uint32_t CMAR3;
    volatile uint32_t reserved3;

    volatile uint32_t CCR4;
    volatile uint32_t CNDTR4;
    volatile uint32_t CPAR4;
    volatile uint32_t CMAR4;
    volatile uint32_t reserved4;

    volatile uint32_t CCR5;
    volatile uint32_t CNDTR5;
    volatile uint32_t CPAR5;
    volatile uint32_t CMAR5;
    volatile uint32_t reserved5;

    volatile uint32_t CCR6;
    volatile uint32_t CNDTR6;
    volatile uint32_t CPAR6;
    volatile uint32_t CMAR6;
    volatile uint32_t reserved6;

    volatile uint32_t CCR7;
    volatile uint32_t CNDTR7;
    volatile uint32_t CPAR7;
    volatile uint32_t CMAR7;
    volatile uint32_t reserved7;
} Dma_Stypes;


#endif // DMA_H
