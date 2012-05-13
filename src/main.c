/*
 * @Author  : Simon Fojtu
 * @Date    : 25.12.2011
 */

#include "defs.h"

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <util/atomic.h>

#include "spi.h"
#include "hw.h"
#include "3310_routines.h"
#include "time.h"
#include "buttons.h"


/* Global variables */
/* time since startup in 1/TIMER0_OVF_FREQ s */
volatile long mtime;
/* device status */
status_t stat;

static char mtc;

/******************************************************************************
 * Functions declarations
 */


/******************************************************************************
 * Functions definitions
 */

/*!
 * Timer0 overflow interrupt handling routine
 */
ISR(TIMER0_OVF_vect)
{
        /* frequency TIMER0_OVF_FREQ Hz */
        mtime++;
}


void main_init(void)
{
        spi_init();

        hw_init();

        timer0_init();

        LCD_init();

        mtime = 0;
        mtc = 0;
}

void main_tick(void)
{
        /* Update time */
        ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
                stat.ltime = mtime;
        }
        stat.sec = stat.ltime / TIMER0_OVF_FREQ;

        /* Process buttons */
        Keyboard_tick(&stat);

        /* Slow tick */
        if (mtc == 255) {
                hw_read_tick(&stat);

                hw_write_tick(&stat);

                mtc = 0;
        }

        mtc++;
}

int main(void)
{

        main_init();

        timer0_start();

        sei();

        while (1) {
                main_tick();
                _delay_ms(10);
        }

        return(0);
}

