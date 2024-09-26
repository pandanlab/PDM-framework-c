#include "flash.h"

void Flash_Unlock(){
    if((FLASH->CR & (1 << 7)) != 0){
        FLASH->KEYR = 0x45670123;
        FLASH->KEYR = 0xCDEF89AB;
    }
}

void Flash_Lock(){
    FLASH->CR |= (1 << 7);
}

void Flash_eraseFlash(uint32_t Address){
    Flash_Unlock();
    while((FLASH->SR & (1 << 0)) != 0);
    FLASH->CR |= (1 << 1);
    FLASH->AR = Address;
    FLASH->CR |= (1 << 6);
    while((FLASH->SR & (1 << 0)) != 0);
    FLASH->CR &= ~(1 << 1);
    Flash_Lock();
}

void Flash_writeFlash(uint32_t Address, uint16_t Data){
    Flash_Unlock();
    while((FLASH->SR & (1 << 0)) != 0);
    FLASH->CR |= (1 << 0);
    FLASH->AR = Address;
    *(volatile uint16_t*)Address = Data;
    while((FLASH->SR & (1 << 0)) != 0);
    FLASH->CR &= ~(1 << 0);
    Flash_Lock();
}


uint8_t Flash_ReadByte(uint32_t Address){
	Flash_Unlock();
	uint8_t data = *(volatile uint8_t*)Address;
	Flash_Lock();
	return data;
}

uint16_t Flash_ReadHaftword(uint32_t Address){
	Flash_Unlock();
	uint16_t data = *(volatile uint16_t*)Address;
	Flash_Lock();
	return data;
}


uint32_t Flash_ReadWord(uint32_t Address){
	Flash_Unlock();
	uint32_t data = *(volatile uint32_t*)Address;
	Flash_Lock();
	return data;
}

void Flash_writeByte(uint32_t Address, uint8_t Data){
	uint16_t target_data = 0;
	uint32_t target_address = Address;
	if(target_address % 2 == 0){
		uint16_t dem1 = (int16_t)Data;
		uint16_t dem2 = ((Flash_ReadHaftword(target_address)>>8)<<8);
		target_data = dem1 | dem2;
		Flash_writeFlash(target_address, target_data);
	}
	else{
		uint16_t dem1,dem2;
		target_address -=1;
		dem1 = ((uint16_t)Data)<<8;
		dem2 = Flash_ReadHaftword(target_address);
		dem2 = dem2<<8;
		dem2 = dem2>>8;
		target_data = dem1 | dem2;
		Flash_writeFlash(target_address, target_data);
	}
}

void Flash_writeHaftword(uint32_t Address, uint16_t Data){
	Flash_writeFlash(Address, Data);
}

void Flash_writeWord(uint32_t Address, uint32_t Data){
	uint16_t target_data;
	target_data = (uint16_t)Data;
	Flash_writeFlash(Address,target_data);
	target_data = (uint16_t)(Data>>16);
	Flash_writeFlash(Address+2,target_data);
}
