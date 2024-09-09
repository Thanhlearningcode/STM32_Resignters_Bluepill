#ifndef _FLASH_H_
#define _FLASH_H_
#include "stm32f10x.h"
void Flash_write(volatile uint32_t adress_start,volatile uint16_t * data,volatile uint32_t size);
void Flash_read(volatile uint32_t adress_start,volatile uint32_t * data,volatile uint32_t size);
void FLash_erase(volatile uint32_t adress_start);
void FLash_read_half_word(volatile uint32_t adress_start,volatile uint16_t * data,volatile uint32_t size);
#endif 