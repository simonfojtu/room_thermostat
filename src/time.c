#include "time.h"

/*!
 * Timer0, 8bit
 */
void timer0_init(void)
{
	/* prescale clk_IO/1024
	 * 7372800/2^8/256
	 * overflow frequency = 112.5Hz
	 */
	TCCR0 |= 1<<CS02;

	/* Timer0 initial value */
	TCNT0 = 0;
}

void timer0_start(void)
{
	/* Enable Timer0 overflow interrupt */
	TIMSK |= 1<<TOIE0;
}


/*!
 * Timer1, 16bit
 */
void timer1_init(void)
{
	/* no prescale */
	TCCR1B |= (1<<CS10);
	/* Timer1 start value */
	TCNT1 = 0;
}

void timer1_start(void)
{
	/* Enable Timer1 overflow interrupt */
	TIMSK |= (1<<TOIE1);
}

void timer1_stop(void)
{
	/* Disable Timer1 overflow interrupt */
	TIMSK &= ~(1<<TOIE1);
}

/*!
 * Timer1 overflow interrupt handling routine.
 */
//ISR(TIMER1_OVF_vect)
//{
//	/* frequency 112.5 Hz */
//}

/*!
 * Timer2, 8bit
 */
void timer2_init(void)
{
	/* no prescale */
//	TCCR2 |= (1<<CS20);
	/* 1/8 */
//	TCCR2 |= (1<<CS21);
	/* 1/32 */
	TCCR2 |= (1<<CS21) | (1<<CS20);
	/* Timer1 start value */
	TCNT2 = 0;

	/* Speaker */
	DDRD |= (1<<PD7);

}

void timer2_start(void)
{
	/* Enable Timer1 overflow interrupt */
	TIMSK |= (1<<OCIE2);
}

void timer2_stop(void)
{
	/* Disable Timer1 overflow interrupt */
	TIMSK &= ~(1<<OCIE2);
}

void timer2_set_freq(char freq)
{
	OCR2 = 0xff - freq;
}

/*!
 * Timer1 overflow interrupt handling routine.
 */
ISR(TIMER2_COMP_vect)
{
	PORTD ^= 1<<PD7;
}
