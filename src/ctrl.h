/*
 * @Author  : Simon Fojtu
 * @Date    : 24.06.2011
 */

#ifndef __CTRL_H_
#define __CTRL_H_

#include "defs.h"

typedef struct Ctrl Ctrl;
struct Ctrl {
        /* deviation */
        int e;
        /* sum of deviations */
        int e_sum;
        /* setpoint */
        int sp;
        /* period */
        int period;
        /* start time */
        int t0;
        /* end time */
        int t1;
        /* min pulse width */
        int t1_min;
        /* action max threshold */
        int T_act;
        /* P const. */
        int P;
        /* I const. */
        int I;
};

void ctrl_init(Ctrl *c);
void ctrl_tick(Ctrl *c, status_t *s);

#endif

