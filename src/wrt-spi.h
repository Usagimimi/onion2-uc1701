#ifndef _WRT_SPI_H_
#define _WRT_SPI_H_

#include <stdlib.h>
#include <unistd.h>

#include <fcntl.h>
#include <sys/ioctl.h>

#ifndef __APPLE__
#include <linux/types.h>
#include <linux/spi/spidev.h>
#endif

#include <string.h>
#include <stdio.h>
#include <stdint.h>
#include <errno.h>


#define SPI_DEV_PATH				"/dev/spidev%d.%d"
#define SPI_PRINT_BANNER			"wrt-spi::"

#define SPI_DEV_INSMOD_TEMPLATE 	"insmod spi-gpio-custom bus%d=%d,%d,%d,%d,%d,%d,%d"

#define SPI_BUFFER_SIZE				32

#define SPI_DEFAULT_SPEED			100000
#define SPI_DEFAULT_BITS_PER_WORD	0 				// corresponds to 8 bits per word
#define SPI_DEFAULT_MODE 			SPI_MODE_0
#define SPI_DEFAULT_MODE_BITS		(SPI_MODE_0 | SPI_TX_DUAL | SPI_RX_DUAL)

#define SPI_DEFAULT_GPIO_SCK		6
#define SPI_DEFAULT_GPIO_MOSI		18
#define SPI_DEFAULT_GPIO_MISO		1
#define SPI_DEFAULT_GPIO_CS			7


#define SPI_CPHA		0x01
#define SPI_CPOL		0x02

#define SPI_MODE_0		(0|0)
#define SPI_MODE_1		(0|SPI_CPHA)
#define SPI_MODE_2		(SPI_CPOL|0)
#define SPI_MODE_3		(SPI_CPOL|SPI_CPHA)

#define SPI_CS_HIGH		0x04
#define SPI_LSB_FIRST	0x08
#define SPI_3WIRE		0x10
#define SPI_LOOP		0x20
#define SPI_NO_CS		0x40
#define SPI_READY		0x80
#define SPI_TX_DUAL		0x100
#define SPI_TX_QUAD		0x200
#define SPI_RX_DUAL		0x400
#define SPI_RX_QUAD		0x800

// type definitions
typedef struct spiParams {
	int 	busNum;
	int 	deviceId;

	int		speedInHz;
	int 	delayInUs;
	int 	bitsPerWord;

	int 	mode;
	int 	modeBits;

	int 	sckGpio;
	int 	mosiGpio;
	int 	misoGpio;
	int 	csGpio;
} spiParams;

// for debugging
#ifndef __APPLE__
	#define SPI_ENABLED		1
#endif


#ifdef __cplusplus
extern "C"{
#endif 





//// spi functions
// initialize the spiParams structure to default values
void 	spiParamInit			(spiParams *params);

// check if an SPI device is mapped sysfs
int 	spiCheckDevice 			(int busNum, int devId);

// register an SPI device with sysfs
int 	spiRegisterDevice 		(spiParams *params);
// setup paramaters of the sysfs SPI interface
int 	spiSetupDevice 			(spiParams *params);

// transfer data through the SPI interface
int 	spiTransfer				(spiParams *params, uint8_t *txBuffer, uint8_t *rxBuffer, int bytes);


int 	spiWrite				(spiParams *params, int addr, uint8_t *wrBuffer, int bytes);
int 	spiRead					(spiParams *params, int addr, uint8_t *rdBuffer, int bytes);


#ifdef __cplusplus
}
#endif 
#endif // _WRT_SPI_H_ 
