#include <stm32f051x8.h>
#include "DAC_integr.h"

void DAC_integr_init(){
	RCC->AHBENR |= (0x1 << 17);		//GPIOA clocking
	GPIOA->MODER |= (3 << 4*2);		//PA4 analog mode
	GPIOA->OSPEEDR |= (3 << 4*2);	//PA4 high speed
	RCC->APB1ENR |= RCC_APB1ENR_DACEN;	//DAC clocking
	DAC1->CR |= DAC_CR_EN1;	//disable output buffer for better dynamic characteristics and enable DAC
}

void DAC_integr_write(int data){
	DAC1->DHR12R1 = data;
}
