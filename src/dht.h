/*
 * @Author  : Simon Fojtu
 * @Date    : 27.05.2012
 */

#ifndef __DHT_H_
#define __DHT_H_

/*
 * Code for communicating with DHT11 sensor
 */

/*
 * Set up according to wiring
 */
#define DHT11_PIN PA1
#define DHT11_IN PINA
#define DHT11_OUT PORTA
#define DHT11_DDR DDRA

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

