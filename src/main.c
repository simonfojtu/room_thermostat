/*
 * @Author  : Simon Fojtu
 * @Date    : 12.02.2011
 */

#include "defs.h"

/* storing controller constants */
//#include "eeprom.h"
/* PID controller */
#include "ctrl.h"
/* buttons */
#include "buttons.h"
/* logger */
#ifdef UART_LOG
#ifndef UART_ENABLED
#error Uart not enabled but uart log is enabled!
#endif
#include "logger.h"
#endif
/* communication with PC */
#ifdef UART_ENABLED
#include "uart.h"
#endif
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


#ifndef NULL
#define NULL 0
#endif

/* Device status */
Context ctx;

volatile long mtime;
int mtc = 0;

int initialize(void)
{
	/* Initialize stat */
	ctx.ltime = 0;
#ifdef USE_KTY
	ctx.t0 = 0;
#endif
        ctx.t1 = 0;

        // Default settings
	ctx.t1_sp = eeprom_read_dword(EEPROM_T1) - 0xffff;
        ctx.ctrl_mode = CTRL_HYST;

	/* Init SPI */
	spi_init();

	/* Init uart */
#ifdef UART_ENABLED
	uart_init();
	uart_enable();
	uart_puts("uart OK\n");
	uart_disable();
#endif

	hw_init();
	Keyboard_init(&ctx);

	/* Init timer0 */
	timer0_init();
	/* Speaker */
//	timer2_init();

	/* Logger */
#ifdef UART_LOG
	log_init();
#endif

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
#ifdef UART_LOG
		log_tick(&ctx);
#endif
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

