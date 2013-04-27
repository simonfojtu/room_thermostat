/*
 * @Author  : Simon Fojtu
 * @Date    : 12.02.2011
 */

#include "defs.h"

/* PID controller */
#include "ctrl.h"
/* buttons */
#include "buttons.h"
/* Nokia 3310 LCD */
#include "3310_routines.h"
/* Timers */
#include "time.h"
/* SPI */
#include "spi.h"
/* HW wrapper */
#include "hw.h"
/* GUI */
#include "gui.h"
/* setting storage */
#include "eeprom.h"

#include <util/delay.h>
#include <util/atomic.h>

/* Device status */
Context ctx;

volatile long mtime;
int mtc = 0;

int initialize(void)
{
	/* Initialize stat */
	ctx.ltime = 0;
        ctx.t1 = 0;

        // Default settings
	ctx.t1_sp = eeprom_read_dword(EEPROM_T1) - 0xffff;
        ctx.ctrl_mode = CTRL_HYST;

	/* Init SPI */
	spi_init();


	hw_init();
	Keyboard_init(&ctx);

	/* Init timer0 */
	timer0_init();

	/* interrupt time */
	mtime = 0;

	LCD_init();
	return 0;
}

/*!
 * Timer0 overflow interrupt handling routine
 */
ISR(TIMER0_OVF_vect)
{
	/* frequency 112.5 Hz */
	mtime++;
}

void main_tick(void)
{
	/* Update time */
	ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
		ctx.ltime = mtime;
	}
	ctx.sec = ctx.ltime / TIMER0_OVF_FREQ;

	Keyboard_tick(&ctx);

	if (mtc >= 10) {
		/* Blink LED */
		PORTB ^= (1<<PB1);

		hw_read_tick(&ctx);

		gui_tick(&ctx);

		hw_write_tick(&ctx);
		
		mtc = 0;
	}

	mtc++;
}

int main(void)
{

	/* Run initialization routine */
	initialize();

	/* start time */
	timer0_start();

	sei();

	for (;;) {
		main_tick();
		_delay_ms(10);
	}
	return 0;
}

