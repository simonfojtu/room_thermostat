#ifndef _time_c_
#define _time_c_

#include <avr/interrupt.h>

/*!
 * Calculation of interrupts to count before stopping the robot.
 * 16bit timer is used for the timing (overflow interrupt), thus
 * the division by 65536.
 */
//#define TIME_LIMIT_INTS (F_CPU/65536*TIME_LIMIT_SEC)


void timer0_init(void);
void timer0_start(void);
#define TIMER0_OVF_FREQ 112.5


void timer1_init(void);
void timer1_start(void);
void timer1_stop(void);
//ISR(TIMER1_OVF_vect);

void timer2_init(void);
void timer2_start(void);
void timer2_stop(void);
void timer2_set_freq(char freq);
ISR(TIMER2_COMP_vect);


#endif
