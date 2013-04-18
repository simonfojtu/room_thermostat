/*!
 * \file eeprom.c
 */
#include "eeprom.h"

/*!
 * ATMEGA16 eeprom size in bytes
 */
#define EEPROM_MEMORY_SIZE 512

/*!
 * Writes data char into eeprom.
 *
 * \return 1 if address is out of range \n 0 otherwise
 * A read might be performed after writing to ensure
 * successful writing.
 */
int eeprom_write(unsigned int uiAddress, unsigned char ucData)
{
	if ( uiAddress < EEPROM_MEMORY_SIZE) {
		char cSREG;
		cSREG = SREG;
		cli();

		/* Wait for completion of previous write */
		while (EECR & (1<<EEWE))
			;
		/* Set up address and data registers */
		EEAR = uiAddress;
		EEDR = ucData;
		/* Write logical one to EEMWE */
		EECR |= (1<<EEMWE);
		/* Start eeprom write by setting EEWE */
		EECR |= (1<<EEWE);

		SREG = cSREG;
		return ( 0 );
	} else {
		return ( 1 );
	}
}

/*!
 * Reads from eeprom.
 */
unsigned char eeprom_read(unsigned int uiAddress)
{
	/* Wait for completion of previous write */
	while (EECR & (1<<EEWE))
		;
	/* Set up address register */
	EEAR = uiAddress;
	/* Start eeprom read by writing EERE */
	EECR |= (1<<EERE);
	/* Return data from data register */
	return EEDR;
}

