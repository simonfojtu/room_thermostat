/*
 * @Author  : Simon Fojtu
 * @Date    : 13.05.2011
 */

#include "spi.h"


/*--------------------------------------------------------------------------
  Name         :  spi_init
  Description  :  Initialising atmega SPI for using with 3310 LCD
  Argument(s)  :  None.
  Return value :  None.
--------------------------------------------------------------------------*/
//SPI initialize
//clock rate: 250000hz
void spi_init(void)
{
	DDRB |= (1<<PB2) | (1<<PB3) | (1<<PB5);
	DDRB &= ~(1<<PB4);
	SPCR = ( (1<<SPE)|(1<<MSTR) | (1<<SPR1) |(1<<SPR0));	// Enable SPI, Master, set clock rate fck/128
}

void WriteByteSPI(unsigned char byte)
{

	SPDR = byte;					//Load byte to Data register
	while (!(SPSR & (1<<SPIF))); 	// Wait for transmission complete

}

char ReadByteSPI(char addr)
{
	SPDR = addr;					//Load byte to Data register
	while (!(SPSR & (1<<SPIF))); 	// Wait for transmission complete
	addr=SPDR;
	return addr;
}
