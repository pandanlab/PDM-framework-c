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

void Flash_eraseFlash(uint32_t Address);
void Flash_writeFlash(uint32_t Address, uint16_t Data);

void Flash_readByte(uint32_t Address);
void Flash_readHaftword(uint32_t Address);
void Flash_readWord(uint32_t Address);

void Flash_writeByte(uint32_t Address, uint8_t Data);
void Flash_writeHaftword(uint32_t Address, uint16_t Data);
void Flash_writeWord(uint32_t Address, uint32_t Data);

#endif