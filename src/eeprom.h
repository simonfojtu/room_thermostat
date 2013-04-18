#ifndef __EEPROM_H_
#define __EEPROM_H_

#include <avr/interrupt.h>
#include <avr/eeprom.h>

int eeprom_write(unsigned int uiAddress, unsigned char ucData);
unsigned char eeprom_read(unsigned int uiAddress);

#endif
