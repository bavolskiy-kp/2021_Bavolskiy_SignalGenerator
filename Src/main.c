#include <main.h>
#include "DAC_devices.h"

int main(void)
{
	init_periphery();
    while(1){
    	DATA_update();		//every cycle iteration check update flag and, if needed, update sample array
    	DATA_output();		//then output samples (one per iteration)
    }
}
