/*
 * @Author  : Simon Fojtu
 * @Date    : 13.05.2011
 */

#ifndef __SPI_H_
#define __SPI_H_

#include <avr/io.h>

void spi_init(void);
void WriteByteSPI(unsigned char byte);
char ReadByteSPI(char addr);


#endif

