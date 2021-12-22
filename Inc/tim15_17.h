#ifndef TIM15_17_H_
#define TIM15_17_H_

#define TIM17_start TIM17->CR1|=TIM_CR1_CEN

void TIM15_init();
void TIM17_init();
void TIM15_delay(int delay_time, int prescaler);

#endif /* TIM15_17_H_ */
