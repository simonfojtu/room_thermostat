/*
 * @Author  : Simon Fojtu
 * @Date    : 27.05.2012
 */

#include "dht.h"

#include <util/delay.h>

#define MAXTRANSITIONS 85


#define DHT11_GET_IN()   ( DHT11_IN & (1<<DHT11_PIN))
#define DHT11_OUT_LOW()  ( DHT11_OUT &= (~(1 << DHT11_PIN)) )
#define DHT11_OUT_HIGH() ( DHT11_OUT |= (1 << DHT11_PIN) )
#define DHT11_DIR_IN()   ( DHT11_DDR &= (~(1 << DHT11_PIN )) )
#define DHT11_DIR_OUT()  ( DHT11_DDR |= (1 << DHT11_PIN) )


int DHT11_read(uint8_t * temp, uint8_t * humidity)
{
    uint8_t counter, laststate;
    uint8_t data[5];
    int i, j;

    DHT11_DIR_OUT();

    /* MCU Start signal */
    // low for 20ms
    DHT11_OUT_LOW();
    _delay_ms(20);

    // high for 40us
    DHT11_OUT_HIGH();
    _delay_us(40);


    /* Response signal is handled within the loop*/
    j = 0;
    laststate = DHT11_GET_IN();
    for (i = 0; i < MAXTRANSITIONS; ++i) {
        counter = 0;
        while (DHT11_GET_IN() == laststate) {
            ++counter;
            _delay_us(1);
            if (counter == 255)
                return(1);
        }

        laststate = DHT11_GET_IN();

        // ignore first 4 transitions - sensor response
        if ((i >= 4) && (i%2 == 0)) {
            data[j/8] <<=1; // shift to write next bit
            if (counter > 30)
                data[j/8] |= 1; // write '1'

            ++j;
        }
    }

    /* Check if we've read at least 40 bits and the checksum matches */
    if ((j < 40) || (data[4] != data[0] + data[1] + data[2] + data[3]))
        return(2);

    /* Parse the data */
    *humidity = data[0];
    *temp = data[2];

    return 0;
}

