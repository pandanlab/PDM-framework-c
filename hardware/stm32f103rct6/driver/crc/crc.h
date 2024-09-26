#if !defined(CRC_H)
#define CRC_H

#include <stdint.h>


typedef struct
{
    volatile uint32_t DR;
    volatile uint32_t IDR;
    volatile uint32_t CR;
}CRC_Types;


#define CRC_BASEADDR              0x40023000
#define CRC                       ((CRC_Types*)CRC_BASEADDR)

#endif // CRC_H
