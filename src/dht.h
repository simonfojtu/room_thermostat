/*
 * @Author  : Simon Fojtu
 * @Date    : 27.05.2012
 */

#ifndef __DHT_H_
#define __DHT_H_

#include <avr/io.h>

/*
 * Code for communicating with DHT11 sensor
 */

/*
 * Set up according to wiring
 */
#define DHT11_PIN PD4
#define DHT11_IN PIND
#define DHT11_OUT PORTD
#define DHT11_DDR DDRD

/* The above can be moved to another file. so we check again, if all is set */
#ifndef DHT11_PIN
#error | DHT11 PIN not defined!
#endif
#ifndef DHT11_IN
#error | DHT11 IN not defined!
#endif
#ifndef DHT11_OUT
#error | DHT11 OUT not defined!
#endif
#ifndef DHT11_DDR
#error | DHT11 DDR not defined!
#endif


int DHT11_read(uint8_t * temp, uint8_t * humidity);


#endif

