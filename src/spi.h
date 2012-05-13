/*
 * @Author  : Simon Fojtu
 * @Date    : 11.01.2012
 */

#ifndef __SPI_H_
#define __SPI_H_

#include <avr/io.h>


inline void spi_init(void);
inline void WriteByteSPI(unsigned char byte);

#endif
