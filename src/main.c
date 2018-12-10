#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <time.h>
#include <sys/time.h>
#include "uc1701.h"

int main()
{

	printf("Testing UC1701 driver now.\n");

	//init random values generator (needed for demo)
	srand(time(NULL));

	//GPIO configuration of display
	uc1701_initparams_t params  = {
		.mosi = 8,	//MOSI
		.sclk = 7,	//SCLK
		.cs = 6,	//CS
		.led = -1,	//LED backlight (unused)
		.rst = 3,	//reset
		.rs = 1,	//D/C
		.speedInHz = 1000000 
	};

	bool initOkay = UC1701_Init(&params);
	if(!initOkay) {
		printf("[-] Failed to initialize UC1701 display!\n");
		return -1;
	}

	UC1701_Contrast(4,44);

	UC1701_Orientation(scr_normal);
	UC1701_Fill(0xAA);

	UC1701_Flush();

	//free it
	UC1701_DeInit();

	return 0;
}
