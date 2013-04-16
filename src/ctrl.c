/*
 * @Author  : Simon Fojtu
 * @Date    : 24.06.2011
 */

#include "ctrl.h"
#include "3310_routines.h"
#include <stdlib.h>

void ctrl_init(Ctrl *c)
{
	/* Write initialization routine here */

	/* output pin */
	DDRD |= 1<<PD5;

	c->e_sum = 0;
	c->t0 = -1;
}

void ctrl_tick(Ctrl *c, status_t *s)
{
	static int action;

	/* Start of the period */
	if (c->t0 == -1)
		c->t0 = s->ltime;

	/* deviation */
	c->e = s->t1_sp - s->t1;
	/* integration */
	c->e_sum += c->I * c->e;

	switch (s->ctrl_mode) {
	case CTRL_OFF:
		action = 0;
		break;
	case CTRL_CONST:
		action = c->P * c->e + c->e_sum;
		break;
	case CTRL_RAMP:
		// TODO implement ramp following
                break;
        case CTRL_HYST:
                if (c->e > 1)
                        action = c->T_act;
                if (c->e < -1)
        		action = 0;
		break;
	}

	c->t1 = action * c->period / c->T_act;
	/* saturation */
	if (c->t1 > c->period)
		c->t1 = c->period;

	/* minimal action */
	if (c->t1 < c->t1_min)
		c->t1 = 0;

	/* Generate PWM */
	if (s->ltime < c->t0 + c->t1) {
		PORTD |= 1<<PD5;
	} else if (s->ltime < c->t0 + c->period) {
		PORTD &= ~(1<<PD5);
	} else {
		c->t0 = -1;
	}

	char buffer[10];

	LCD_gotoXY(0,4);
	switch (s->ctrl_mode) {
	case(CTRL_CONST):
		LCD_writeChar('-');
		break;
	case(CTRL_RAMP):
		LCD_writeChar('/');
		break;
	case(CTRL_HYST):
		LCD_writeChar('t');
		break;
	case(CTRL_OFF):
		LCD_writeChar('x');
		break;
	}
	LCD_writeChar(' ');
	LCD_writeString_F(ltoa(c->I, buffer, 10));
	LCD_writeChar(' ');
	LCD_writeString_F(ltoa(c->P, buffer, 10));
	LCD_writeChar('_');

	LCD_gotoXY(0,5);
	LCD_writeString_F(ltoa(c->e, buffer, 10));
	LCD_writeChar(' ');
	LCD_writeString_F(ltoa(action, buffer, 10));
	LCD_writeChar(' ');
	LCD_writeString_F(ltoa(c->e_sum, buffer, 10));
	LCD_writeChar('_');


}

