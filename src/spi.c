/*
 * @Author  : Simon Fojtu
 * @Date    : 11.01.2012
 */

#include "spi.h"
#include "defs.h"

/*--------------------------------------------------------------------------
  Name         :  spi_init
  Description  :  Initialising atmega SPI for using with 3310 LCD
  Argument(s)  :  None.
  Return value :  None.
--------------------------------------------------------------------------*/
//SPI initialize
inline void spi_init(void)
{
        /* output MOSI=PB5, SCK=PB7, SS=PB4 */
        USIDDR |= (1<<USIMOSI) | (1<<USISCK) | (1<<USISS);
        /* input MISO=PB6 */
        USIDDR &= ~(1<<USIMISO);

        SPCR = ( (1<<SPE)|(1<<MSTR) | (1<<SPR1) |(1<<SPR0));    // Enable SPI, Master, set clock rate fck/128
}


void WriteByteSPI(unsigned char byte)
{

        SPDR = byte;					//Load byte to Data register
        while (!(SPSR & (1<<SPIF))); 	// Wait for transmission complete

}

