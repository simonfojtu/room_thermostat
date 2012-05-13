/*
 * @Author  : Simon Fojtu
 * @Date    : 24.06.2011
 */

#include "ctrl.h"
#include "3310_routines.h"

#include <stdlib.h>
#include <avr/io.h>

void ctrl_init(Ctrl *c)
{
        /* set output pin */
        INIT_CTRL_PINS;

        /* Init PI controller */
        c->P = 1;
        c->I = 0;
        c->period = 1125; // = 10 s
        c->t1_min = 113; // 1 s
        c->T_act = 200; // = 20 deg C
        c->e_sum = 0;
        c->t0 = -1;
}

void ctrl_tick(Ctrl *c, status_t *s)
{
        /* TODO PID according to http://brettbeauregard.com/blog/2011/04/improving-the-beginners-pid-introduction/ */
        int action = 0;

        /* Start of the period */
        if (c->t0 == -1)
                c->t0 = s->ltime;

        /* deviation */
        c->e = s->t1_sp - s->t1;
        /* integration */
        c->e_sum += c->I * c->e;

        switch (s->ctrl_mode) {
        case CTRL_MAN:
        case CTRL_AUTO:
                action = c->P * c->e + c->e_sum;
                break;
        default: // CTRL_OFF, ...
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
                SET_CTRL_PIN;
        } else if (s->ltime < c->t0 + c->period) {
                CLEAR_CTRL_PIN;
        } else {
                c->t0 = -1;
        }

        LCD_gotoXY(0,4);
        switch (s->ctrl_mode) {
        case(CTRL_MAN):
                LCD_writeChar('m');
                break;
        case(CTRL_AUTO):
                LCD_writeChar('a');
                break;
        case(CTRL_OFF):
                LCD_writeChar('x');
                break;
        default:
                break;
        }
}

