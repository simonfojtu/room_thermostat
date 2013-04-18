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
	long period;
	/* start time */
	long t0;
	/* end time */
	long t1;
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
void ctrl_tick(Ctrl *c, Context *s);

#endif

