//#define EXPERIMENT	//macros for experiment part

//periphery libraries
#include "tim15_17.h"
#include "DAC_devices.h"
#include "DAC_integr.h"
#include "R2R.h"
#include "button.h"
#include "signals.h"

struct SIGNAL_STRUCT signal_struct = {0, 0, 2048, 10, 0, 50};	//structure to combine all signal parameters and signal samples, made for convenience

void EXTI0_1_IRQHandler(){	//function for detecting button press
	EXTI->PR |= EXTI_PR_PIF0;	//clear pending bit on interrupt line 0
	TIM17_start;	//delay for contact bounce removing
	GPIOA->MODER |= GPIO_MODER_MODER0;	//change GPIOA mode to disable interruption on rising edge, caused by contact bounce
}

void TIM17_IRQHandler(){	//function for flag updating
	GPIOA->MODER &= ~GPIO_MODER_MODER0;		//change GPIOA mode to enable interruption on rising edge
	if((GPIOA->IDR & GPIO_IDR_0) == GPIO_IDR_0){	//check if after delay time button is still pressed
		signal_struct.update_flag = 1;	//update flag if button is pressed
	}
	TIM17->SR &= ~TIM_SR_UIF;	//clear update flag of TIM17 to disable interruption on update
}

//function pointer array below needed for function type selection without ifs
void (*signal_types[])(const int T, unsigned int magnitude, int *digital_array, int param) = {sinus, squarewave_unipolar, triangle, sawtooth, constant};

void init_periphery(){		//device periphery initialization
#ifdef EXPERIMENT
	ChangeClockSpeed();		//change clock speed to determine device limits
#endif //EXPERIMENT
	R2R_init();		//R2R initialization
	DAC_integr_init();		//integrated DAC initialization
	button_init();		//button for frequency change initialization
	TIM15_init();		//TIM15 for output frequency control initialization
	TIM17_init();		//TIM17 for contact bounce removing initialization
	signal_struct.sample_period = 1000000/(signal_struct.frequency*samples_num);	//calculate delay between samples
	(*signal_types[signal_struct.type])(samples_num, signal_struct.magnitude, signal_struct.samples, signal_struct.param);	//fill array with samples of desired signal
}

void DATA_update(){		//update array after button is pressed
	if (signal_struct.update_flag){		//check if update flag is set
		signal_struct.frequency += 50;		//increase frequency by 100 Hz (?)
		signal_struct.sample_period = 1000000/(signal_struct.frequency*samples_num);	//update delay
		(*signal_types[signal_struct.type])(samples_num, signal_struct.magnitude, signal_struct.samples, signal_struct.param);	//update array
		signal_struct.update_flag = 0;	//clear update flag
	}
}

void DATA_output(){		//output signal sample
	static int i = 0;	//sample index
	DAC_integr_write(signal_struct.samples[i]);		//output sample to DAC
	R2R_write(signal_struct.samples[i++]);		//output sample to R2R
	if (i == samples_num)		//check if sample index equals sample array length
		i = 0;		//set sample index to zero
	TIM15_delay(signal_struct.sample_period, 3);		//delay to control output frequency
}

#ifdef EXPERIMENT
void ChangeClockSpeed(){		//change clock speed to 48 MHz
	RCC->CR &= ~RCC_CR_PLLON; //disable PLL
	RCC->CFGR |= (0xA << 18); //mul PLL input clock by 12 so PLL clock will be 48 MHz
	RCC->CR |= RCC_CR_PLLON; //enable PLL
	while(!(RCC->CR & RCC_CR_PLLRDY)); //wait for PLL to be ready
	RCC->CFGR |= (2 << 0); //switch sys clock source to PLL
	while (!(RCC->CFGR & RCC_CFGR_SWS_PLL)); //wait for sys clock to switch
}
#endif //EXPERIMENT
