#ifndef SIGNALS_H_
#define SIGNALS_H_

void constant(const int T, unsigned int magnitude, int *digital_array, int dummy_arg);
void sinus(int T, unsigned int magnitude, int *digital_array, int dummy_arg);
void squarewave_unipolar(const int T, unsigned int magnitude, int *digital_array, int duty_cycle);
void triangle(int T, unsigned int magnitude, int *digital_array, int dummy_arg);
void sawtooth(int T, unsigned int magnitude, int *digital_array, int dummy_arg);

#endif //SIGNALS_H_
