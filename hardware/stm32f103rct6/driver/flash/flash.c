#include "flash.h"

void Flash_Unlock(){
    // Check if Flash is already unlocked
    if((FLASH->CR & (1 << 7)) != 0){
        FLASH->KEYR = 0x45670123;
        FLASH->KEYR = 0xCDEF89AB;
    }
}

void Flash_Lock(){
    FLASH->CR |= (1 << 7);
}

void Flash_EraseSector(uint32_t Sector){
    Flash_Unlock();
    while((FLASH->SR & (1 << 0)) != 0);

    // Enable the sector erase operation
    FLASH->CR |= (1 << 1); // Set the PER bit (Page Erase)

    // Set the sector address
    FLASH->AR = Sector;

    FLASH->CR |= (1 << 6); // Set the STRT bit (Start Erase)

    // Wait until the operation is complete
    while((FLASH->SR & (1 << 0)) != 0);

    // Clear the sector erase bit
    FLASH->CR &= ~(1 << 1); // Clear the PER bit

    // Lock the Flash
    Flash_Lock();
}

void Flash_ProgrameWord(uint32_t Address, uint16_t Data){
    Flash_Unlock();

    // Wait until Flash is ready
    while((FLASH->SR & (1 << 0)) != 0);

    //select program
    FLASH->CR |= (1 << 0);

    // Set the address
    FLASH->AR = Address;

    // Set data
    *(volatile uint16_t*)Address = Data;

    // Wait until the operation is complete
    while((FLASH->SR & (1 << 0)) != 0);

    // Clear the programming bit
    FLASH->CR &= ~(1 << 0); // Clear the PG bit

    // Lock the Flash
    Flash_Lock();
}


uint32_t Flash_ReadWord(uint32_t Address){
	Flash_Unlock();
	uint32_t data = *(volatile uint16_t*)Address;
	Flash_Lock();
	return data;
}