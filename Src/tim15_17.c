#include <stm32f051x8.h>
#include "tim15_17.h"

void TIM15_init(){
	RCC->APB2ENR |= RCC_APB2ENR_TIM15EN;	//TIM15 clocking
	TIM15->CR1 |= TIM_CR1_OPM;		//one pulse mode, needed to start every count from 0
}

void TIM17_init(){
	RCC->APB2ENR |= RCC_APB2ENR_TIM17EN;	//TIM17 clocking
	TIM17->CR1 |= TIM_CR1_OPM;		//one pulse mode, needed to start every count from 0
	TIM17->DIER |= TIM_DIER_UIE;	//interrupt on update event
	TIM17->ARR = 5000-1;	//this line and one below set delay for 1s
	TIM17->PSC = 800-1;
	NVIC_SetPriority(TIM17_IRQn, 5);	//set priority for TIM17 interrupt
	NVIC_EnableIRQ(TIM17_IRQn);		//enable TIM17 interrupt
}

void TIM15_delay(int delay_time, int prescaler){		//delay in us
	TIM15->ARR = delay_time-1;
	TIM15->PSC = prescaler;
	TIM15->CR1 |= TIM_CR1_CEN;
	while(!(TIM15->SR & TIM_SR_UIF));		//wait for update flag to set
	TIM15->SR &= ~TIM_SR_UIF;		//clear update flag
}
