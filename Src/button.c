#include <stm32f051x8.h>
#include "button.h"

void button_init(){
	RCC->AHBENR |= RCC_AHBENR_GPIOAEN;
//	SYSCFG->EXTICR[0] |= (1 << 0);
	EXTI->IMR |= EXTI_IMR_IM0;
	EXTI->RTSR |= EXTI_RTSR_RT0;
	NVIC_SetPriority(EXTI0_1_IRQn, 10);
	NVIC_EnableIRQ(EXTI0_1_IRQn);
}
