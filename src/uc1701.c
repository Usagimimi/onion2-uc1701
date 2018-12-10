#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>  //#include <delay.h>
#include <fcntl.h>

#include "wrt-spi.h" /* main SPI functionality */
#include "ugpio.h" /* for GPIO stuff */


#include "uc1701.h"
#include "font5x7.h"


/* saved gpio pins (freed later) */
static int savedRS	= -1;
static int savedRst = -1;
static int savedCs	= -1;
static int savedLED = -1;

/* SPI params (must be saved for calls to read/write) */
static struct spiParams params;

uint16_t                  scr_width       = SCR_W;
uint16_t                  scr_height      = SCR_H;
ScrOrientation_TypeDef    scr_orientation = scr_normal;

uint8_t vRAM[SCR_W * SCR_H / 8]; // Display buffer


/*************************************************************************************/
/*                              GPIO support function                                */
/*************************************************************************************/

/* static function declarations */
static bool UC1701_InitOutputGPIO(int gpio);
static void UC1701_SetOutputGPIO(int gpio, int value);
static void UC1701_FreeGPIOs();

static bool UC1701_InitOutputGPIO(int gpio)
{
	if(gpio < 0) return false;
	unsigned int gpio_u = (unsigned int) gpio;
	//use ugpio.
	//is the gpio already requested by somebody else?
	int err;
	if ((err = gpio_is_requested(gpio_u)) < 0)
	{
		printf("[-] GPIO %d already requested.\n", gpio);
		return false;
	}

	//export GPIO if necessary
	if (!err)
	{
		printf("Exporting GPIO %d\n", gpio);
		if ((err = gpio_request(gpio_u, NULL)) < 0)
		{
			printf("[-] Requesting GPIO %d failed.\n", gpio);
			return false;
		}
	}

	if((err = gpio_direction_output(gpio_u, 1)) < 0)
	{
		printf("[-] Setting GPIO %d to output mode failed.\n", gpio);
		return false;
	}

	return true;
}

//Just a wrapper for gpio_set_value
static void UC1701_SetOutputGPIO(int gpio, int value)
{
	if (gpio < 0)
	{
		return;
	}
	gpio_set_value((unsigned int)gpio, value);
}

static void UC1701_FreeGPIOs()
{
	if(savedRS != -1)
	{
		gpio_free(savedRS);
		savedRS = -1; //prevent double freeing
	}

	if(savedRst != -1)
	{
		gpio_free(savedRst);
		savedRst = -1;
	}

	if(savedCs != -1)
	{
		gpio_free(savedRst);
		savedRst = -1;
	}

	if(savedLED != -1)
	{
		gpio_free(savedLED);
		savedLED = -1;
	}
}

/*************************************************************************************/
/*                         Low level LCD  support function                           */
/*************************************************************************************/
static void UC1701_write(uint8_t data)
{
	uint8_t dummyRXBuf;

	//transmit SPI data
	dummyRXBuf = 0;
	int err = spiTransfer(&params, &data, &dummyRXBuf, 1);
	if(err == EXIT_FAILURE)
		printf("[-] SPI transfer failed!\n");
}

static void UC1701_cmd(uint8_t cmd)
{
	//UC1701_SetOutputGPIO(savedCs, 0);
	UC1701_SetOutputGPIO(savedRS, 0);
	//transmit SPI data
	uint8_t cmdCopy = cmd;
	uint8_t dummyRXBuf = 0;

	int err = spiTransfer(&params, &cmdCopy, &dummyRXBuf, 1);
	if(err == EXIT_FAILURE)
	{
		printf("[-] SPI transfer failed!\n");
	}
	//UC1701_SetOutputGPIO(savedCs, 1);
}

static void UC1701_cmd_double(uint8_t cmd1, uint8_t cmd2) {
	UC1701_cmd(cmd1);
	UC1701_cmd(cmd2);
}

static void UC1701_data(uint8_t data)
{
	UC1701_SetOutputGPIO(savedRS, 1);
	UC1701_write(data);
}

uint16_t RGB565(uint8_t R,uint8_t G,uint8_t B) {
	return ((R >> 3) << 11) | ((G >> 2) << 5) | (B >> 3);
}

/*************************************************************************************/
/*                                     LCD  function                                 */
/*************************************************************************************/
int UC1701_Init(uc1701_initparams_t *initParams)
{
	printf("[-] Init function called.\n");
	//activate debug logging
	//onionSetVerbosity(ONION_VERBOSITY_EXTRA_VERBOSE);

	int err = 0;

	if(!initParams)
		return false;

	//check if all required GPIOs are set
	if(initParams->cs_s < 0 || initParams->mosi < 0 || initParams->sclk < 0 || initParams->rs < 0) {
		printf("[-] Required GPIO pin not set.\n");
		return false;
	}

	//use default values at first
	spiParamInit(&params);
	params.mosiGpio = initParams->mosi;
	params.sckGpio = initParams->sclk;
	params.csGpio = initParams->cs_h; // don't touch!!!
	params.speedInHz = initParams->speedInHz;
	params.modeBits = SPI_MODE_3;//SPI_3WIRE | SPI_NO_CS | 
	params.busNum = 1; //this comes from my local machine. no idea if it works elsewhere.. (ls /dev/spi*)
	params.deviceId = 32766;
	params.delayInUs = 10;

	//is our device already mapped?
	err = spiCheckDevice(params.busNum, params.deviceId);
	if(err == EXIT_FAILURE) {
		printf("[-] spiCheckDevice() failed.\n");
		return false;
	}

	//register ourselves
	err = spiRegisterDevice(&params);
	if(err == EXIT_FAILURE)  {
		printf("spiRegisterDevice() failed.\n");
		return false;
	}
	printf("[+] SPI register device okay.\n");

	err = spiSetupDevice(&params);
	if(err == EXIT_FAILURE)  {
		printf("spiSetupDevice() failed.\n");
		return false;
	}

	//set GPIO for DC (data/command selection, on the board called "RS")
	if(initParams->rs > 0)
	{
		savedRS = initParams->rs;
		UC1701_InitOutputGPIO(initParams->rs);
	}

	//reset line (optional)
	if(initParams->rst > 0)
	{
		savedRst = initParams->rst;
		UC1701_InitOutputGPIO(initParams->rst);
	}
	
	if(initParams->cs_s > 0)
	{
		savedCs = initParams->cs_s; // software CS
		UC1701_InitOutputGPIO(savedCs);
		UC1701_SetOutputGPIO(savedCs, 0);
	}

	//LED line (turn display on/off, optional)
	if(initParams->led > 0) {
		savedLED = initParams->led;
		UC1701_InitOutputGPIO(initParams->led);
	}

	usleep(10 * 1000);

	//pulse reset pin
	if(initParams->rst > 0)
	{
		UC1701_SetOutputGPIO(savedCs, 1);
		UC1701_SetOutputGPIO(savedRst, 0);
		usleep(2 * 1000);					 // Must hold RST low at least 1ms
		UC1701_SetOutputGPIO(savedRst, 1);
		usleep(6 * 1000);					 // Wait at least 5ms
	}

	//usleep(10 * 1000);

	UC1701_Reset();
	UC1701_SetOutputGPIO(savedCs, 0);
	UC1701_PowerControl(true, true, true); //UC1701_cmd(0x2f); // Power control: Boost ON,  V.Regular ON,  V.Follower ON
	UC1701_SetOutputGPIO(savedCs, 1);

    UC1701_BiasRatio(UC1701BiasRatio_0);
    UC1701_SetDisplayState(UC1701Enable_On);
    UC1701_Orientation(UC1701Orientation_Normal);
    UC1701_Contrast(4, 34 + 5);
}

void UC1701_DeInit(void)
{
	//free GPIOs
	UC1701_FreeGPIOs();
	//free SPI bus
}

// Reset display registers
// Doesn't affect the display memory
void UC1701_Reset(void)
{
	UC1701_SetOutputGPIO(savedCs, 0);
	UC1701_cmd(0xe2);
	UC1701_SetOutputGPIO(savedCs, 1);
}

void UC1701_BiasRatio(UC1701BiasRatio ratio)
{
    UC1701_SetOutputGPIO(savedCs, 0);
    UC1701_cmd(0xA2 | (0x01 & (uint8_t)ratio));
    UC1701_SetOutputGPIO(savedCs, 1);
}

// Toggle display on/off
// Input:
//   state: ENABLED or DISABLED
// Doesn't affect the display memory
void UC1701_SetDisplayState(UC1701Enable state)
{
	UC1701_SetOutputGPIO(savedCs, 0);
	UC1701_cmd(state == UC1701Enable_On ? 0xaf : 0xae);
	UC1701_SetOutputGPIO(savedCs, 1);
}

// Set LCD contrast
// Input:
//   res_ratio: internal resistor ratio [0..7], power on value is 4
//   el_vol: electronic volume [0..63], power on value is 32
void UC1701_Contrast(uint8_t res_ratio, uint8_t el_vol)
{
	UC1701_SetOutputGPIO(savedCs, 0);
	UC1701_cmd(0x20 | (res_ratio & 0x07));
	UC1701_cmd_double(0x81,el_vol & 0x3f);
	UC1701_SetOutputGPIO(savedCs, 1);
}

void UC1701_PowerControl(bool isXv0Enable, bool isV0Enable, bool isVgEnable)
{
    uint8_t value = 0;
    if (isXv0Enable)
        value |= (1 << 2);
    if (isV0Enable)
        value |= (1 << 1);
    if (isVgEnable)
        value |= (1 << 0);
        
    UC1701_cmd(0x28 | value);
}

// Set all LCD pixels on or off
// Input:
//   state: ON or OFF
// Doesn't affect the display memory
void UC1701_SetAllPixelOn(OnOffStatus state) {
	UC1701_SetOutputGPIO(savedCs, 0);
	UC1701_cmd(state == ON ? 0xa5 : 0xa4);
	UC1701_SetOutputGPIO(savedCs, 1);
}

// Set inverse display pixels
// Input:
//   state: NORMAL or INVERT
void UC1701_SetInvert(InvertStatus state) {
	UC1701_SetOutputGPIO(savedCs, 0);
	UC1701_cmd(state == NORMAL ? 0xa6 : 0xa7);
	UC1701_SetOutputGPIO(savedCs, 1);
}

// Set X coordinate mapping (normal or mirrored)
// Input:
//   state: NORMAL or INVERT
// Doesn't affect the display memory
void UC1701_SetXDir(InvertStatus MX) {
	UC1701_SetOutputGPIO(savedCs, 0);
	UC1701_cmd(MX == NORMAL ? 0xa0 : 0xa1);
	UC1701_SetOutputGPIO(savedCs, 1);
}

// Set Y coordinate mapping (normal or mirrored)
// Input:
//   state: NORMAL or INVERT
// Doesn't affect the display memory
void UC1701_SetYDir(InvertStatus MY) {
	UC1701_SetOutputGPIO(savedCs, 0);
	UC1701_cmd(MY == NORMAL ? 0xc8 : 0xc0);
	UC1701_SetOutputGPIO(savedCs, 1);
}

// Set display column:page according to pixel coordinates
// Input:
//   X, Y - pixel coordinates
void UC1701_SetAddr(uint8_t X, uint8_t Y) {
	UC1701_SetOutputGPIO(savedCs, 0);
	UC1701_cmd(X & 0x0f); // Column address LSB
	UC1701_cmd((X > 4) | 0x10); // Column address MSB
	UC1701_cmd(((Y / 8) & 0x0f) | 0xb0); // Page
	UC1701_SetOutputGPIO(savedCs, 1);
}

// Set scroll line number
// Input:
//   line - start line number (0..63)
void UC1701_SetScrollLine(uint8_t line) {
	UC1701_SetOutputGPIO(savedCs, 0);
	UC1701_cmd(0x40 | (line & 0x3f));
	UC1701_SetOutputGPIO(savedCs, 1);
}

// Set display orientation
void UC1701_Orientation(uint8_t orientation) {
	UC1701_SetOutputGPIO(savedCs, 0);
	switch(orientation) {
	case scr_CW:
		scr_width  = SCR_H;
		scr_height = SCR_W;
		UC1701_SetXDir(NORMAL);
		UC1701_SetYDir(INVERT);
		break;
	case scr_CCW:
		scr_width  = SCR_H;
		scr_height = SCR_W;
		UC1701_SetXDir(INVERT);
		UC1701_SetYDir(NORMAL);
		break;
	case scr_180:
		scr_width  = SCR_W;
		scr_height = SCR_H;
		UC1701_SetXDir(INVERT);
		UC1701_SetYDir(INVERT);
		break;
	default:
		scr_width  = SCR_W;
		scr_height = SCR_H;
		UC1701_SetXDir(NORMAL);
		UC1701_SetYDir(NORMAL);
		break;
	}
	scr_orientation = orientation;
	UC1701_SetOutputGPIO(savedCs, 1);
}

// Send vRAM buffer content into display
void UC1701_Flush(void) {
	uint16_t i,j;

	UC1701_SetOutputGPIO(savedCs, 0);
	for (j = 0; j < 8; j++) {
		 // Column 0 address LSB
		if (scr_orientation == scr_180 || scr_orientation == scr_CCW) UC1701_cmd(0x04); else UC1701_cmd(0x00);
		UC1701_cmd(0x10); // Column 0 address MSB
		UC1701_cmd(0xb0 | j); // Page address
		for (i = 0; i < SCR_W; i++) {
			UC1701_data(vRAM[(j * SCR_W) + i]);
		}
	}
	UC1701_SetOutputGPIO(savedCs, 1);
}

// Fill VRam memory with specified pattern
void UC1701_Fill(uint8_t pattern) {
	memset(vRAM,pattern,sizeof(vRAM));
//	for (i = 0; i < sizeof(vRAM); i++) vRAM[i] = pattern;
}

// Set pixel in vRAM buffer
void UC1701_SetPixel(uint8_t X, uint8_t Y) {
	uint8_t XX = X;
	uint8_t YY = Y;

	if (scr_orientation == scr_CW || scr_orientation == scr_CCW) {
		XX = Y; YY = X;
	}
	vRAM[((YY >> 3) * SCR_W) + XX] |= 1 << (YY % 8);
//	vRAM[((Y >> 3) * SCR_W) + X] |= 1 << (Y % 8);
}

// Clear pixel in vRAM buffer
void UC1701_ResetPixel(uint8_t X, uint8_t Y) {
	uint8_t XX = X;
	uint8_t YY = Y;

	if (scr_orientation == scr_CW || scr_orientation == scr_CCW) {
		XX = Y; YY = X;
	}
	vRAM[((YY >> 3) * SCR_W) + XX] &= ~(1 << (YY % 8));
//	vRAM[((Y >> 3) * SCR_W) + X] &= ~(1 << (Y % 8));
}

void UC1701_HLine(uint8_t X1, uint8_t X2, uint8_t Y, PSetReset_TypeDef SR) {
	uint8_t x;

	if (SR == PSet) {
		for (x = X1; x <= X2; x++) UC1701_SetPixel(x,Y);
	} else {
		for (x = X1; x <= X2; x++) UC1701_ResetPixel(x,Y);
	}
}

void UC1701_VLine(uint8_t X, uint8_t Y1, uint8_t Y2, PSetReset_TypeDef SR) {
	uint8_t y;

	if (SR == PSet) {
		for (y = Y1; y <= Y2; y++) UC1701_SetPixel(X,y);
	} else {
		for (y = Y1; y <= Y2; y++) UC1701_ResetPixel(X,y);
	}
}

void UC1701_Rect(uint8_t X1, uint8_t Y1, uint8_t X2, uint8_t Y2, PSetReset_TypeDef SR) {
	UC1701_HLine(X1,X2,Y1,SR);
	UC1701_HLine(X1,X2,Y2,SR);
	UC1701_VLine(X1,Y1 + 1,Y2 - 1,SR);
	UC1701_VLine(X2,Y1 + 1,Y2 - 1,SR);
}

void UC1701_FillRect(uint8_t X1, uint8_t Y1, uint8_t X2, uint8_t Y2, PSetReset_TypeDef SR) {
	uint8_t y;

	for (y = Y1; y <= Y2; y++) UC1701_HLine(X1,X2,y,SR);
}

void UC1701_Line(int16_t X1, int16_t Y1, int16_t X2, int16_t Y2) {
	int16_t dX = X2-X1;
	int16_t dY = Y2-Y1;
	int16_t dXsym = (dX > 0) ? 1 : -1;
	int16_t dYsym = (dY > 0) ? 1 : -1;

	if (dX == 0) {
		if (Y2 > Y1) UC1701_VLine(X1,Y1,Y2,PSet); else UC1701_VLine(X1,Y2,Y1,PSet);
		return;
	}
	if (dY == 0) {
		if (X2 > X1) UC1701_HLine(X1,X2,Y1,PSet); else UC1701_HLine(X2,X1,Y1,PSet);
		return;
	}

	dX *= dXsym;
	dY *= dYsym;
	int16_t dX2 = dX << 1;
	int16_t dY2 = dY << 1;
	int16_t di;

	if (dX >= dY) {
		di = dY2 - dX;
		while (X1 != X2) {
			UC1701_SetPixel(X1,Y1);
			X1 += dXsym;
			if (di < 0) {
				di += dY2;
			} else {
				di += dY2 - dX2;
				Y1 += dYsym;
			}
		}
	} else {
		di = dX2 - dY;
		while (Y1 != Y2) {
			UC1701_SetPixel(X1,Y1);
			Y1 += dYsym;
			if (di < 0) {
				di += dX2;
			} else {
				di += dX2 - dY2;
				X1 += dXsym;
			}
		}
	}
	UC1701_SetPixel(X1,Y1);
}

void UC1701_Ellipse(uint16_t X, uint16_t Y, uint16_t A, uint16_t B) {
	int16_t Xc = 0, Yc = B;

	long A2 = (long)A*A, B2 = (long)B*B;
	long C1 = -(A2/4 + A % 2 + B2);
	long C2 = -(B2/4 + B % 2 + A2);
	long C3 = -(B2/4 + B % 2);
	long t = -A2 * Yc;
	long dXt = B2*Xc*2, dYt = -A2*Yc*2;
	long dXt2 = B2*2, dYt2 = A2*2;
	while (Yc >= 0 && Xc <= A) {
		UC1701_SetPixel(X + Xc,Y + Yc);
		if (Xc != 0 || Yc != 0) UC1701_SetPixel(X - Xc,Y - Yc);
		if (Xc != 0 && Yc != 0) {
			UC1701_SetPixel(X + Xc,Y - Yc);
			UC1701_SetPixel(X - Xc,Y + Yc);
		}
		if (t + Xc*B2 <= C1 || t + Yc*A2 <= C3) {
			Xc++;
			dXt += dXt2;
			t   += dXt;
		} else if (t - Yc*A2 > C2) {
			Yc--;
			dYt += dYt2;
			t   += dYt;
		} else {
			Xc++;
			Yc--;
			dXt += dXt2;
			dYt += dYt2;
			t   += dXt;
			t   += dYt;
		}
	}
}

void UC1701_PutChar5x7(uint8_t X, uint8_t Y, uint8_t Char, Opaque_TypeDef bckgnd) {
	uint16_t i,j;
	uint8_t buffer[5],tmpCh;

	memcpy(buffer,&Font5x7[(Char - 32) * 5],5);

	if (bckgnd == opaque) {
	    for (i = 0; i < 5; i++) {
	    	tmpCh = buffer[i];
	    	for (j = 0; j < 8; j++) {
	    		if ((tmpCh >> j) & 0x01) UC1701_SetPixel(X + i,Y + j); else UC1701_ResetPixel(X + i,Y + j);
	    	}
	    }
	} else {
		for (i = 0; i < 5; i++) {
			tmpCh = buffer[i];
			for (j = 0; j < 8; j++) {
				if ((tmpCh >> j) & 0x01) UC1701_SetPixel(X + i,Y + j);
			}
		}
	}
}

void UC1701_PutStr5x7(uint8_t X, uint8_t Y, char *str, Opaque_TypeDef bckgnd) {
    while (*str) {
        UC1701_PutChar5x7(X,Y,*str++,bckgnd);
        if (X < scr_width - 6) { X += 6; } else if (Y < scr_height - 8) { X = 0; Y += 8; } else { X = 0; Y = 0; }
    };
}

void UC1701_PutInt5x7(uint8_t X, uint8_t Y, uint32_t num, Opaque_TypeDef bckgnd) {
	char str[11]; // 10 chars max for UINT32_MAX
	int i = 0;

	do { str[i++] = num % 10 + '0'; } while ((num /= 10) > 0);
	int strLen = i;
	for (i--; i >= 0; i--) UC1701_PutChar5x7(X + (strLen * 6) - ((i + 1) * 6),Y,str[i],bckgnd);
}

void UC1701_PutHex5x7(uint8_t X, uint8_t Y, uint32_t num, Opaque_TypeDef bckgnd) {
	char str[11]; // 10 chars max for UINT32_MAX
	int i = 0;

	do { str[i++] = "0123456789ABCDEF"[num % 0x10]; } while ((num /= 0x10) > 0);
	str[i++] = 'x';
	str[i++] = '0';

	int strLen = i;

	for (i--; i >= 0; i--) UC1701_PutChar5x7(X + (strLen * 6) - ((i + 1) * 6),Y,str[i],bckgnd);
}
