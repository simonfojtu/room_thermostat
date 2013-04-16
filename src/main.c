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
status_t stat;

volatile long mtime;
int mtc = 0;

int initialize(void)
{
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
	Keyboard_init();

	/* Initialize stat */
	stat.ltime = 0;
#ifdef USE_KTY
	stat.t0 = 0;
#endif
        stat.t1 = 0;

        // Default settings
	stat.t1_sp = eeprom_read_dword(EEPROM_T1) - 0xffff;
        stat.ctrl_mode = CTRL_HYST;

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
		stat.ltime = mtime;
	}
	stat.sec = stat.ltime / TIMER0_OVF_FREQ;

	Keyboard_tick(&stat);

	if (mtc >= 10) {
		/* Blink LED */
		PORTB ^= (1<<PB1);

		hw_read_tick(&stat);

		gui_tick(&stat);
#ifdef UART_LOG
		log_tick(&stat);
#endif
		hw_write_tick(&stat);
		
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

