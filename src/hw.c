/*
 * @Author  : Simon Fojtu
 * @Date    : 19.06.2011
 */

#include "hw.h"

#include <avr/io.h>

/* reading temperature from DS18B20 */
#include "onewire.h"
#include "ds18x20.h"
/* controller */
#include "ctrl.h"

Ctrl t1_ctrl;

void hw_init()
{
	/* Status LED */
	DDRB |= (1<<PB1);

	/* Init onewire */
#ifndef OW_ONE_BUS
	ow_set_bus(&PINB,&PORTB,&DDRB,PB0);
#endif

	/* Init PI controller */
	t1_ctrl.P = 1;
	t1_ctrl.I = 0;
	t1_ctrl.period = 11250; // = 100 s
	t1_ctrl.t1_min = 1125; // 10 s
	t1_ctrl.T_act = 200; // = 20 deg C
	ctrl_init(&t1_ctrl);
}

void hw_read_tick(Context * ctx)
{

	/* DS */
	if (DS18X20_conversion_in_progress() == DS18X20_CONVERSION_DONE) {
		if (DS18X20_read_decicelsius_single(DS18B20_FAMILY_CODE, &ctx->t1) == DS18X20_OK) {
			ctx->temp_status = DS_OK;
		} else {
			ctx->temp_status = DS_READ_ERROR;
		}
		if (DS18X20_start_meas(DS18X20_POWER_EXTERN, NULL) != DS18X20_OK) {
			ctx->temp_status = DS_MEAS_ERROR;
		}
	}
}

void hw_write_tick(Context * ctx)
{
	ctrl_tick(&t1_ctrl, ctx);
}

