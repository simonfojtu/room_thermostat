/*
 * @Author  : Simon Fojtu
 * @Date    : 19.06.2011
 */

#include "hw.h"

#include <avr/io.h>

/* reading temperature from DS18B20 */
#include "onewire.h"
#include "ds18x20.h"
/* keyboard */
#include "buttons.h"
/* controller */
#include "ctrl.h"

Ctrl ctrl;

void hw_init()
{
        /* Init onewire */
#ifndef OW_ONE_BUS
        ow_set_bus(&OW_IN,&OW_OUT,&OW_DDR,OW_PIN);
#endif

        /* Init keyboard */
        INIT_BUTTONS_PINS;

        ctrl_init(&ctrl);
}

void hw_read_tick(status_t * stat)
{

        /* DS */
        if (DS18X20_conversion_in_progress() == DS18X20_CONVERSION_DONE) {
                if (DS18X20_read_decicelsius_single(DS18B20_FAMILY_CODE, &stat->t1) == DS18X20_OK) {
                        stat->ds_status = DS_OK;
                } else {
                        stat->ds_status = DS_READ_ERROR;
                }
                if (DS18X20_start_meas(DS18X20_POWER_EXTERN, NULL) != DS18X20_OK) {
                        stat->ds_status = DS_MEAS_ERROR;
                }
        }
}

void hw_write_tick(status_t * stat)
{
        ctrl_tick(&ctrl, stat);
}

