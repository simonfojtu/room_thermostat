#include "time.h"
#include <avr/interrupt.h>


/*!
 * Timer0, 8bit
 */
void timer0_init(void)
{
        /* prescale clk_{I/O}/1024
         * f_ovf = 7372800/2^8/1024
         * overflow frequency = 28.125Hz
         */
        TCCR0 |= 1<<CS02 | 1<<CS00;
        /* Timer0 initial value */
        TCNT0 = 0;
}

void timer0_start(void)
{
        /* Enable Timer0 overflow interrupt */
        TIMSK |= 1<<TOIE0;
}

