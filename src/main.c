#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <time.h>
#include <sys/time.h>
#include "uc1701.h"

int main(int argc, char * argv[])
{

	int i;
	int pattern = 0;
	int contrast = 5;

	printf("Testing UC1701 driver now.\n");

	if(argc == 2)
	{
		sscanf(argv[1], "%d", &pattern);
	}
	
	if(argc == 3)
	{
		sscanf(argv[1], "%d", &pattern);
		sscanf(argv[2], "%d", &contrast);
	}
	
	//init random values generator (needed for demo)
	srand(time(NULL));

	//GPIO configuration of display
	uc1701_initparams_t params  = {
		.mosi = 8,	//MOSI
		.sclk = 7,	//SCLK
		.cs_h = 6,	//CS hardware don't touch!!!
		.cs_s = 0,	//CS sowftware
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

	UC1701_Contrast(4, 34 + contrast);
	printf(" Contrast set to %d\n", contrast);

	UC1701_Fill(pattern);
	printf(" Pattern set to %d\n", pattern);

	UC1701_Flush();

	//free it
	UC1701_DeInit();

	return 0;
}
