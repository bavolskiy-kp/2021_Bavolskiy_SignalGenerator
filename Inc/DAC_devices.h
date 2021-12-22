#ifndef DAC_DEVICES_H_
#define DAC_DEVICES_H_
#include <stm32f051x8.h>

#define samples_num 32

struct SIGNAL_STRUCT{
	int update_flag;
	int type;						//0x00 - sine;	0x01 - squarewave;	0x02 - triangle;
									//0x03 - sawtooth;	0x04 - white noise; 0x05 - const
	unsigned int magnitude;			//from 0 to 3 V with a step = 0.73 mV
	unsigned int frequency;			//from 0 to 31250 Hz with a step = 1 Hz (for integrated DAC)
									//from 0 to 250000 (?) Hz with a step = 1 Hz (for R2R DAC)
	int sample_period;
	int param;						//used only for squarewave (duty cycle)
	int samples[samples_num];
};

void EXTI0_1_IRQHandler();
void TIM17_IRQHandler();
void init_periphery();
void DATA_update();
void DATA_output();
void ChangeClockSpeed();

#endif /* DAC_DEVICES_H_ */
