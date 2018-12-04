#ifndef __UC1701_H__
#define __UC1701_H__

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

/* structure for initialization paramters */
typedef struct {
	//pins
	int mosi, sclk, cs, rst, rs, led;
	//speed
	int speedInHz;
} uc1701_initparams_t;

typedef enum {ON = 0, OFF = !ON} OnOffStatus;
typedef enum {NORMAL = 0, INVERT = !NORMAL} InvertStatus;
typedef enum {ENABLED = 0, DISABLED = !ENABLED} DisplayState;

// Screen dimensions
#define  SCR_W 132
#define  SCR_H 64

typedef enum {
	transparent  = 0,
	opaque       = 1
} Opaque_TypeDef;

typedef enum {
	PSet = 1,
	PReset = 0
} PSetReset_TypeDef;

typedef enum {
	scr_normal = 0,
	scr_CW     = 1,
	scr_CCW    = 2,
	scr_180    = 3
} ScrOrientation_TypeDef;


extern uint16_t scr_width;
extern uint16_t scr_height;


void UC1701_Init(void);
void UC1701_DeInit(void);
void UC1701_Contrast(uint8_t res_ratio, uint8_t el_vol);
void UC1701_SetAllPixelOn(OnOffStatus state);
void UC1701_SetInvert(InvertStatus state);
void UC1701_SetDisplayState(DisplayState state);
void UC1701_SetXDir(InvertStatus MX);
void UC1701_SetYDir(InvertStatus MY);
void UC1701_SetAddr(uint8_t X, uint8_t Y);
void UC1701_SetScrollLine(uint8_t line);
void UC1701_Orientation(uint8_t orientation);

void UC1701_Flush(void);
void UC1701_Fill(uint8_t pattern);
void UC1701_SetPixel(uint8_t X, uint8_t Y);
void UC1701_ResetPixel(uint8_t X, uint8_t Y);

void UC1701_HLine(uint8_t X1, uint8_t X2, uint8_t Y, PSetReset_TypeDef SR);
void UC1701_VLine(uint8_t X, uint8_t Y1, uint8_t Y2, PSetReset_TypeDef SR);
void UC1701_Rect(uint8_t X1, uint8_t Y1, uint8_t X2, uint8_t Y2, PSetReset_TypeDef SR);
void UC1701_FillRect(uint8_t X1, uint8_t Y1, uint8_t X2, uint8_t Y2, PSetReset_TypeDef SR);
void UC1701_Line(int16_t X1, int16_t Y1, int16_t X2, int16_t Y2);
void UC1701_Ellipse(uint16_t X, uint16_t Y, uint16_t A, uint16_t B);

void UC1701_PutChar5x7(uint8_t X, uint8_t Y, uint8_t Char, Opaque_TypeDef bckgnd);
void UC1701_PutStr5x7(uint8_t X, uint8_t Y, char *str, Opaque_TypeDef bckgnd);
void UC1701_PutInt5x7(uint8_t X, uint8_t Y, uint32_t num, Opaque_TypeDef bckgnd);
void UC1701_PutHex5x7(uint8_t X, uint8_t Y, uint32_t num, Opaque_TypeDef bckgnd);

#endif // __UC1701_H__
