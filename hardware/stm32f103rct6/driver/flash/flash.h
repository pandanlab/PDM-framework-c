#ifndef FLASH_H
#define FLASH_H

#include<stdint.h>
typedef struct{
	volatile uint32_t ACR;
	volatile uint32_t KEYR;
	volatile uint32_t OPTKEYR;
	volatile uint32_t SR;
	volatile uint32_t CR;
	volatile uint32_t AR;
	volatile uint32_t Reserved;
	volatile uint32_t OBR;
	volatile uint32_t WRPR;
}Flash_Types;

#define FLASH_BASEADDR     0x40022000UL
#define FLASH              ((Flash_Types *) FLASH_BASEADDR)

void Flash_Unlock();
void Flash_Lock();
void Flash_EraseSector(uint32_t Sector);
void Flash_ProgrameWord(uint32_t Address, uint16_t Data);
uint32_t Flash_ReadWord(uint32_t Address);

#endif
