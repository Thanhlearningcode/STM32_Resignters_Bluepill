#include "ADC_Library.h"

void ADC_Config(void)
{
	//enable clock for ADC1
	RCC->APB2ENR |= (1<<9); 
	//Config prescaler for ADC clock (clock of ADC must exceed 14Mhz)
	RCC->CFGR &= ~(0x3 << 14);
	RCC->CFGR |= (0x2<<14);
	//Config ADC
	ADC1->CR1 |= (1<<5); //enable interrupt when end of coversion
	ADC1->CR1 |= (1<<8); //enable scan mode
	ADC1->CR1 &= ~(1<<11); // disable discontinous mode
	ADC1->CR1 &= ~(0xF<<16); //Enable independent mode
	
	ADC1->CR2 |= (1<<1); //enable conitnous coversion
	ADC1->CR2 &= ~(1<<8); //disable DMA mode
	ADC1->CR2 &= ~(1<<11); //choose right align mode for data register
	ADC1->CR2 |= (0x7<<17); //using software to start ADC
	ADC1->CR2 |= (1<<20); //Enable external trigger event
	
	ADC1->SMPR2 &= ~(0x7<<0);
	ADC1->SMPR2 |= (0x6<<0);//choose sample time equal 71.5 cycles
	ADC1->SMPR2 &= ~(0x7<<3);
	ADC1->SMPR2 |= (0x6<<3); //choose sample time equal 71.5 cycles
	ADC1->SMPR2 &= ~(0x7<<6);
	ADC1->SMPR2 |= (0x6<<6);//choose sample time equal 71.5 cycles
	ADC1->SQR1 &= ~(0xF<<20); //Config regular length of channels
	ADC1->SQR1 |= (0x2<<20); // group of 3 channel
	ADC1->SQR3 = 0U;
	ADC1->SQR3 |= (0<<0); //first to coversion for channel 0
	ADC1->SQR3 |= (0x1<<5); //second to coversion for channel 1
	ADC1->SQR3 |= (0x2<<10); //third to coversion for channnel 2
	
	//Enable ADC peripheral
	ADC1->CR2 |= (1<<0);
	ADC1->CR2 |= (1<<22); //trigger by software to start ADC
}