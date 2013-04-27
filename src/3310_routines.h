//********************************************************
//****  Header file for 3310_routines.c  *****
//********************************************************
//Controller:	ATmega32 (Clock: 1 Mhz-internal)
//Compiler:		ImageCraft ICCAVR
//Author:		CC Dharmani, Chennai (India)
//Date:			Sep 2008
//********************************************************
#ifndef _3310_ROUTINES_H_

#define _3310_ROUTINES_H_

#include <avr/io.h>
//#include <avr/pgmspace.h>

#define SET_DC_PIN                 PORTB |= 1 << PB1
#define CLEAR_DC_PIN               PORTB &= ~(1 << PB1)
#define SET_SCE_PIN                PORTB |= 1 << PB2
#define CLEAR_SCE_PIN              PORTB &= ~(1 << PB2)
#define SET_RST_PIN                PORTB |= 1 << PB0
#define CLEAR_RST_PIN              PORTB &= ~(1 << PB0)

#define MEGA_FONT_DOT 10
#define MEGA_FONT_PLUS 11
#define MEGA_FONT_MINUS 12

#define SMALL_FONT_SPACE 10
#define SMALL_FONT_CIRC 11
#define SMALL_FONT_DOT 12
#define SMALL_FONT_C 13
#define SMALL_FONT_f 14
#define SMALL_FONT_o 15


/*--------------------------------------------------------------------------------------------------
                                 Public function prototypes
--------------------------------------------------------------------------------------------------*/
void LCD_init ( void );
void LCD_clear ( void );
void LCD_gotoXY ( unsigned char x, unsigned char y );
void LCD_writeChar ( unsigned char character );
void LCD_writeChar_megaFont ( unsigned char character );
void LCD_writeData ( unsigned char data );
void LCD_writeCommand ( unsigned char command );
void LCD_writeString_megaFont ( unsigned char *string );
void LCD_writeString_F ( unsigned char *string);
//void LCD_setPixel ( unsigned char x, unsigned char y);
//void LCD_drawLine ( unsigned char x1, unsigned char y1, unsigned char x2, unsigned char y2 );
//void LCD_drawBorder (void );
//void lcd_delay_ms ( int millisec );



//***** Small fonts (5x7) **********

static const unsigned char smallFont[] = {
	0x3E, 0x51, 0x49, 0x45, 0x3E,   // 0
	0x00, 0x42, 0x7F, 0x40, 0x00,   // 1
	0x42, 0x61, 0x51, 0x49, 0x46,   // 2
	0x21, 0x41, 0x45, 0x4B, 0x31,   // 3
	0x18, 0x14, 0x12, 0x7F, 0x10,   // 4
	0x27, 0x45, 0x45, 0x45, 0x39,   // 5
	0x3C, 0x4A, 0x49, 0x49, 0x30,   // 6
	0x01, 0x71, 0x09, 0x05, 0x03,   // 7
	0x36, 0x49, 0x49, 0x49, 0x36,   // 8
	0x06, 0x49, 0x49, 0x29, 0x1E,   // 9
	0x00, 0x00, 0x00, 0x00, 0x00,   // sp
	0x00, 0x06, 0x09, 0x09, 0x06,   // �
	0x00, 0x60, 0x60, 0x00, 0x00,   // .
	0x3E, 0x41, 0x41, 0x41, 0x22,   // C
	0x08, 0x7E, 0x09, 0x01, 0x02,   // f
	0x38, 0x44, 0x44, 0x44, 0x38   // o
        /*
	0x7E, 0x11, 0x11, 0x11, 0x7E,   // A
	0x7F, 0x49, 0x49, 0x49, 0x36,   // B
	0x7F, 0x41, 0x41, 0x22, 0x1C,   // D
	0x7F, 0x49, 0x49, 0x49, 0x41,   // E
	0x7F, 0x09, 0x09, 0x09, 0x01,   // F
	0x3E, 0x41, 0x49, 0x49, 0x7A,   // G
	0x7F, 0x08, 0x08, 0x08, 0x7F,   // H
	0x00, 0x41, 0x7F, 0x41, 0x00,   // I
	0x20, 0x40, 0x41, 0x3F, 0x01,   // J
	0x7F, 0x08, 0x14, 0x22, 0x41,   // K
	0x7F, 0x40, 0x40, 0x40, 0x40,   // L
	0x7F, 0x02, 0x0C, 0x02, 0x7F,   // M
	0x7F, 0x04, 0x08, 0x10, 0x7F,   // N
	0x3E, 0x41, 0x41, 0x41, 0x3E,   // O
	0x7F, 0x09, 0x09, 0x09, 0x06,   // P
	0x3E, 0x41, 0x51, 0x21, 0x5E,   // Q
	0x7F, 0x09, 0x19, 0x29, 0x46,   // R
	0x46, 0x49, 0x49, 0x49, 0x31,   // S
	0x01, 0x01, 0x7F, 0x01, 0x01,   // T
	0x3F, 0x40, 0x40, 0x40, 0x3F,   // U
	0x1F, 0x20, 0x40, 0x20, 0x1F,   // V
	0x3F, 0x40, 0x38, 0x40, 0x3F,   // W
	0x63, 0x14, 0x08, 0x14, 0x63,   // X
	0x07, 0x08, 0x70, 0x08, 0x07,   // Y
	0x61, 0x51, 0x49, 0x45, 0x43,   // Z
	0x20, 0x54, 0x54, 0x54, 0x78,   // a
	0x7F, 0x48, 0x44, 0x44, 0x38,   // b
	0x38, 0x44, 0x44, 0x44, 0x20,   // c
	0x38, 0x44, 0x44, 0x48, 0x7F,   // d
	0x38, 0x54, 0x54, 0x54, 0x18,   // e
	0x0C, 0x52, 0x52, 0x52, 0x3E,   // g
	0x7F, 0x08, 0x04, 0x04, 0x78,   // h
	0x00, 0x44, 0x7D, 0x40, 0x00,   // i
	0x20, 0x40, 0x44, 0x3D, 0x00,   // j
	0x7F, 0x10, 0x28, 0x44, 0x00,   // k
	0x00, 0x41, 0x7F, 0x40, 0x00,   // l
	0x7C, 0x04, 0x18, 0x04, 0x78,   // m
	0x7C, 0x08, 0x04, 0x04, 0x78,   // n
	0x7C, 0x14, 0x14, 0x14, 0x08,   // p
	0x08, 0x14, 0x14, 0x18, 0x7C,   // q
	0x7C, 0x08, 0x04, 0x04, 0x08,   // r
	0x48, 0x54, 0x54, 0x54, 0x20,   // s
	0x04, 0x3F, 0x44, 0x40, 0x20,   // t
	0x3C, 0x40, 0x40, 0x20, 0x7C,   // u
	0x1C, 0x20, 0x40, 0x20, 0x1C,   // v
	0x3C, 0x40, 0x30, 0x40, 0x3C,   // w
	0x44, 0x28, 0x10, 0x28, 0x44,   // x
	0x0C, 0x50, 0x50, 0x50, 0x3C,   // y
	0x44, 0x64, 0x54, 0x4C, 0x44,   // z
	0x00, 0x00, 0x2f, 0x00, 0x00,    // !
	0x00, 0x07, 0x00, 0x07, 0x00,   // "
	0x14, 0x7f, 0x14, 0x7f, 0x14,   // #
	0x24, 0x2a, 0x7f, 0x2a, 0x12,   // $
	0xc4, 0xc8, 0x10, 0x26, 0x46,   // %
	0x36, 0x49, 0x55, 0x22, 0x50,   // &
	0x00, 0x05, 0x03, 0x00, 0x00,   // '
	0x00, 0x1c, 0x22, 0x41, 0x00,   // (
	0x00, 0x41, 0x22, 0x1c, 0x00,   // )
	0x14, 0x08, 0x3E, 0x08, 0x14,   // *
	0x08, 0x08, 0x3E, 0x08, 0x08,   // +
	0x00, 0x00, 0x50, 0x30, 0x00,   // ,
	0x10, 0x10, 0x10, 0x10, 0x10,   // -
	0x20, 0x10, 0x08, 0x04, 0x02,   // /
        */
        /*
	0x00, 0x36, 0x36, 0x00, 0x00,   // :
	0x00, 0x56, 0x36, 0x00, 0x00,   // ;
	0x08, 0x14, 0x22, 0x41, 0x00,   // <
	0x14, 0x14, 0x14, 0x14, 0x14,   // =
	0x00, 0x41, 0x22, 0x14, 0x08,   // >
	0x02, 0x01, 0x51, 0x09, 0x06,   // ?
	0x32, 0x49, 0x59, 0x51, 0x3E,   // @
	0x00, 0x7F, 0x41, 0x41, 0x00,   // [
	0x55, 0x2A, 0x55, 0x2A, 0x55,   // 55
	0x00, 0x41, 0x41, 0x7F, 0x00,   // ]
	0x04, 0x02, 0x01, 0x02, 0x04,   // ^
	0x40, 0x40, 0x40, 0x40, 0x40,   // _
	0x00, 0x01, 0x02, 0x04, 0x00,   // '
                */
};




//******* VERY LARGE FONTS **********
//used here for displaying temperature

static const unsigned char number[13][3][16] = {

	{{0,128,192,224,224,96,224,224,  //'0'
			192,128,0,0,0,0,0,0}
		,
		{112,255,255,1,0,0,0,0,
		 255,255,254,0,0,0,0,0}
		,
		{0,15,31,60,56,48,56,56,
		 31,15,3,0,0,0,0,0}}
	,

	{{0,0,0,0,128,224,224,0, 		   //'1'
			0,0,0,0,0,0,0,0}
		,
		{0,0,3,3,3,255,255,0,
		 0,0,0,0,0,0,0,0}
		,
		{0,0,56,56,56,63,63,56,
		 56,56,0,0,0,0,0,0}}
	,

	{{0,192,192,224,96,96,224,224,   //'2'
			192,128,0,0,0,0,0,0}
		,
		{0,1,0,0,128,192,224,249,
		 63,31,0,0,0,0,0,0}
		,
		{0,60,62,63,63,59,57,56,
		 56,56,56,0,0,0,0,0}}
	,

	{{0,192,224,224,96,96,224,224,   //'3'
			192,192,0,0,0,0,0,0}
		,
		{0,1,0,0,48,48,56,125,
		 239,207,0,0,0,0,0,0}
		,
		{0,28,56,56,48,48,56,60,
		 31,15,1,0,0,0,0,0}}
	,

	{{0,0,0,0,0,128,192,224, 		   //'4'
			224,0,0,0,0,0,0,0}
		,
		{224,240,248,222,207,199,193,255,
		 255,192,192,0,0,0,0,0}
		,
		{0,0,0,0,0,0,0,63,
		 63,0,0,0,0,0,0,0}}
	,

	{{0,224,224,224,224,224,224,224,	//'5'
			224,224,224,0,0,0,0,0}
		,
		{0,63,63,63,56,56,48,112,
		 240,224,0,0,0,0,0,0}
		,
		{0,28,56,56,48,48,56,60,
		 31,15,1,0,0,0,0,0}}
	,

	{{0,0,128,192,192,224,96,96,		//'6'
			224,224,0,0,0,0,0,0}
		,
		{224,254,255,55,57,24,24,56,
		 240,240,192,0,0,0,0,0}
		,
		{0,15,31,28,56,48,48,56,
		 31,15,7,0,0,0,0,0}}
	,

	{{0,224,224,224,224,224,224,224,		 //'7'
			224,224,224,0,0,0,0,0}
		,
		{0,0,0,0,128,224,248,126,
		 31,7,1,0,0,0,0,0}
		,
		{0,0,56,62,31,7,1,0,
		 0,0,0,0,0,0,0,0}}
	,

	{{0,128,192,224,224,96,96,224,		 //'8'
			192,192,0,0,0,0,0,0}
		,
		{0,207,255,127,56,48,112,112,
		 255,239,199,0,0,0,0,0}
		,
		{3,15,31,60,56,48,48,56,
		 31,31,15,0,0,0,0,0}}
	,

	{{0,128,192,224,224,96,224,224,		 //'9'
			192,128,0,0,0,0,0,0}
		,
		{12,63,127,241,224,192,192,225,
		 255,255,254,0,0,0,0,0}
		,
		{0,0,56,48,48,56,56,30,
		 15,7,0,0,0,0,0,0}}
	,


	{{0,0,0,0,0,0,0,0,	  		  		 //'.'
			0,0,0,0,0,0,0,0}
		,
		{0,0,0,0,0,0,0,0,
		 0,0,0,0,0,0,0,0}
		,
		{60,60,60,0,0,0,0,0,
		 0,0,0,0,0,0,0,0}}
	,

	{{0,0,0,0,0,0,0,0,   					 //'+'
			0,0,0,0,0,0,0,0}
		,
		{0,0,64,64,64,64,64,254,
		 254,64,64,64,64,64,0,0}
		,
		{0,0,0,0,0,0,0,15,
		 15,0,0,0,0,0,0,0}}
	,

	{{0,0,0,0,0,0,0,0, 	   				 //'-'
			0,0,0,0,0,0,0,0}
		,
		{0,64,64,64,64,64,64,0,
		 0,0,0,0,0,0,0,0}
		,
		{0,0,0,0,0,0,0,0,
		 0,0,0,0,0,0,0,0}}
};


#endif  //  _3310_ROUTINES_H_
