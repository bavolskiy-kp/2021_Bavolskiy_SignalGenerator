#include <math.h>	//for sin function and PI constant
#include <stm32f051x8.h>
#include "signals.h"

void constant(const int T, unsigned int magnitude, int *digital_array, int dummy_arg){		//last argument needed only in squarewave, in other waveforms used due to way functions are called
	for (int i = 0; i < T; i++){
	        digital_array[i] = magnitude;
	}
}

void sinus(const int T, unsigned int magnitude, int *digital_array, int dummy_arg){
    for (int i = 0; i < T; i++){
        digital_array[i] = 0.5*magnitude*(1+sin(i*2*M_PI/T));
    }
}

void squarewave_unipolar(const int T, unsigned int magnitude, int *digital_array, int duty_cycle){
    int LIMIT = ((float)duty_cycle/100)*T;
	for (int i = 0; i < LIMIT; i++){
		digital_array[i] = magnitude;
    }
    for (int i = LIMIT; i < T; i++){
    	digital_array[i] = 0;
    }
}

void triangle(const int T, unsigned int magnitude, int *digital_array, int dummy_arg){		//isosceles triangle
    int half_T = (float)T/2;
    for (int i = 0; i < half_T; i++){
    	digital_array[i] = (float)(i*magnitude)/half_T;
    }
    for (int i = half_T; i < T; i++){
    	digital_array[i] = (float)((T-i)*magnitude)/half_T;
    }
}

void sawtooth(const int T, unsigned int magnitude, int *digital_array, int dummy_arg){
    for (int i = 0; i < T; i++){
    	digital_array[i] = (float)(i*magnitude)/T;
    }
}
