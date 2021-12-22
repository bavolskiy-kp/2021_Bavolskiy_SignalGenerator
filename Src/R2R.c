#include <stm32f051x8.h>
#include "R2R.h"


void R2R_init(){
	//enable port A & C clocking
	RCC->AHBENR |= (0x1 << 17);
	RCC->AHBENR |= (0x1 << 19);
	//config port A & C pins for output (output mode, high speed)
	for (int i = 16; i < 25; i+=2){
		GPIOA->MODER |= (1 << i);
		GPIOA->OSPEEDR |= (3 << i);
	}
	for (int i = 20; i < 25; i+=2){
		GPIOC->MODER |= (1 << i);
		GPIOA->OSPEEDR |= (3 << i);
	}
}

void R2R_write(int data){
	data = (float)data/4096*256;	//scale data for 8 bit format
	for(int i = 8; i < 13; i++){	//use BSRR and conditional operator to avoid using if/else
		GPIOA->BSRR |= (((data >> (i-8)) & 1) == 1) ? (1 << i) : ((1 << (16+i)) & ~(1 << i));
	}
	for(int i = 10; i < 12; i++){
		GPIOC->BSRR |= (((data >> (i-5)) & 1) == 1) ? (1 << i) : ((1 << (16+i)) & ~(1 << i));
	}
}
