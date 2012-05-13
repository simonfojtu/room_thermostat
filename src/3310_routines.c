//********************************************************
//**** Functions for Interfacing NOKIA 3310 Display *****
//********************************************************
//Controller:	ATmega32 (Clock: 1 Mhz-internal)
//Compiler:		ImageCraft ICCAVR
//Author:		CC Dharmani, Chennai (India)
//Date:			Sep 2008
//********************************************************

#include "3310_routines.h"
#include "spi.h"
#include "defs.h"

#include <avr/io.h>
#include <util/delay.h>

//global variable for remembering where to start writing the next text string on 3310 LCD
unsigned char char_start;


/*--------------------------------------------------------------------------------------------------
  Name         :  LCD_init
  Description  :  LCD controller initialization.
  Argument(s)  :  None.
  Return value :  None.
--------------------------------------------------------------------------------------------------*/
void LCD_init ( void )
{
        /* set output pins */
        INIT_DISPLAY_PINS;

        CLEAR_RST_PIN;	//reset LCD
        _delay_ms(2);

        CLEAR_SCE_PIN;    //Enable LCD

        _delay_ms(2);
        SET_RST_PIN;

        SET_SCE_PIN;	//disable LCD

        LCD_writeCommand( 0x21 );  // LCD Extended Commands.
        LCD_writeCommand( 0xE0 );  // Set LCD Vop (Contrast).
        LCD_writeCommand( 0x04 );  // Set Temp coefficent.
        LCD_writeCommand( 0x13 );  // LCD bias mode 1:48.
        LCD_writeCommand( 0x20 );  // LCD Standard Commands, Horizontal addressing mode.
//    LCD_writeCommand( 0x09 );  // all display segments on
//    _delay_ms(5);
        LCD_writeCommand( 0x0c );  // LCD in normal mode.

        LCD_clear();
}

/*--------------------------------------------------------------------------------------------------
  Name         :  LCD_writeCommand
  Description  :  Sends command to display controller.
  Argument(s)  :  command -> command to be sent
  Return value :  None.
--------------------------------------------------------------------------------------------------*/
void LCD_writeCommand ( unsigned char command )
{
        CLEAR_SCE_PIN;	  //enable LCD

        CLEAR_DC_PIN;	  //set LCD in command mode

        //  Send data to display controller.
        WriteByteSPI(command);

        SET_SCE_PIN;   	 //disable LCD
}

/*--------------------------------------------------------------------------------------------------
  Name         :  LCD_writeData
  Description  :  Sends Data to display controller.
  Argument(s)  :  Data -> Data to be sent
  Return value :  None.
--------------------------------------------------------------------------------------------------*/
void LCD_writeData ( unsigned char data )
{
        CLEAR_SCE_PIN;	  //enable LCD

        SET_DC_PIN;	  //set LCD in Data mode

        //  Send data to display controller.
        WriteByteSPI(data);

        SET_SCE_PIN;   	 //disable LCD
}

/*--------------------------------------------------------------------------------------------------
  Name         :  LCD_clear
  Description  :  Clears the display
  Argument(s)  :  None.
  Return value :  None.
--------------------------------------------------------------------------------------------------*/
void LCD_clear ( void )
{
        uint8_t i,j;

        LCD_gotoXY (0,0);  	//start with (0,0) position

        for (i=0; i<8; i++)
                for (j=0; j<90; j++)
                        LCD_writeData( 0x00 );

        LCD_gotoXY (0,0);	//bring the XY position back to (0,0)

}

/*--------------------------------------------------------------------------------------------------
  Name         :  LCD_gotoXY
  Description  :  Sets cursor location to xy location corresponding to basic font size.
  Argument(s)  :  x - range: 0 to 84
  			   	  y -> range: 0 to 5
  Return value :  None.
--------------------------------------------------------------------------------------------------*/
void LCD_gotoXY ( unsigned char x, unsigned char y )
{
        LCD_writeCommand (0x80 | x);   //column
        LCD_writeCommand (0x40 | y);   //row
}

/*--------------------------------------------------------------------------------------------------
  Name         :  LCD_writeChar
  Description  :  Displays a character at current cursor location and increment cursor location.
  Argument(s)  :  ch   -> Character to write.
  Return value :  None.
--------------------------------------------------------------------------------------------------*/
void LCD_writeChar (unsigned char ch)
{
        unsigned char j;

        LCD_writeData(0x00);

        for (j=0; j<5; j++)
                LCD_writeData( pgm_read_byte(&smallFont [(ch-32)*5 + j] ));

        LCD_writeData( 0x00 );
}

/*--------------------------------------------------------------------------------------------------
  Name         :  LCD_writeChar_megaFont
  Description  :  Displays a character in large fonts, used here for displatying temperature
		  (for displaying '.', '+', '-', and '0' to '9', stored
		  in 3310_routines.h as three dimensional array, number[][][])
  Argument(s)  :  ch   -> Character to write.
  Return value :  None.
--------------------------------------------------------------------------------------------------*/
void LCD_writeChar_megaFont (unsigned char ch)
{
        unsigned char i, j;

        if (ch == '.')
                ch = 10;
        else if (ch == '+')
                ch = 11;
        else if (ch == '-')
                ch = 12;
        else
                ch = ch & 0x0f;


        for (i=0;i<3;i++) {
                LCD_gotoXY (4 + char_start, i+2);

                for (j=0; j<16; j++)
                        LCD_writeData( pgm_read_byte(&number[ch][i][j]));
        }

        if (ch == '.')
                char_start += 5;
        else
                char_start += 12;
}

/*--------------------------------------------------------------------------------------------------
  Name         :  LCD_writeString_megaFont
  Description  :  Displays a string at current location, in large fonts
  Argument(s)  :  string -> Pointer to ASCII string (stored in RAM)
  Return value :  None.
--------------------------------------------------------------------------------------------------*/
void LCD_writeString_megaFont ( unsigned char *string )
{
        char_start = 0;

        while ( *string )
                LCD_writeChar_megaFont( *string++ );

        LCD_gotoXY(char_start+6, 3);
        LCD_writeChar('z'+1); 			  //symbol of Degree
        LCD_writeChar('C');
}

/*--------------------------------------------------------------------------------------------------
  Name         :  LCD_writeString_F
  Description  :  Displays a string stored in FLASH, in small fonts (refer to 3310_routines.h)
  Argument(s)  :  string -> Pointer to ASCII string (stored in FLASH)
  Return value :  None.
--------------------------------------------------------------------------------------------------*/
void LCD_writeString_F ( unsigned char *string )
{
        while ( *string )
                LCD_writeChar( *string++ );
}

/*--------------------------------------------------------------------------------------------------
  Name         :  LCD_drawBorder
  Description  :  Draws rectangle border on the display
  Argument(s)  :  None
  Return value :  None
--------------------------------------------------------------------------------------------------*/
void LCD_drawBorder (void )
{
        unsigned char i, j;

        for (i=0; i<7; i++) {
                LCD_gotoXY (0,i);

                for (j=0; j<84; j++) {
                        if (j == 0 || j == 83)
                                LCD_writeData (0xff);		// first and last column solid fill to make line
                        else if (i == 0)
                                LCD_writeData (0x08);		// row 0 is having only 5 bits (not 8)
                        else if (i == 6)
                                LCD_writeData (0x04);		// row 6 is having only 3 bits (not 8)
                        else
                                LCD_writeData (0x00);
                }
        }
}

/*--------------------------------------------------------------------------------------------------
                                         End of file.
--------------------------------------------------------------------------------------------------*/
