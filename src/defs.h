/*
 * @Author  : Simon Fojtu
 * @Date    : 13.05.2011
 */

#ifndef __DEFS_H_
#define __DEFS_H_

#include <stdint.h>

#include "fsm.h"

/* Uart communication speed */
#define BAUDRATE 9600
/* Events queue buffer size */
#define EVENTS_QUEUE_MAX_SIZE 8

/* DS18B20 status */
#define DS_OK		0
#define DS_READ_ERROR	1
#define DS_MEAS_ERROR	2

enum ctrl_mode_t {
	CTRL_OFF,
	CTRL_CONST,
	CTRL_RAMP,
        CTRL_HYST,
	CTRL_MAX
};

enum event_type {
	EVENT_B_LEFT,
	EVENT_B_RIGHT,
	EVENT_B_MENU,
	EVENT_NOP,
	MAX_EVENTS
};

/*
 * Structure to hold device status
 */
typedef struct {
	/* Time in 1/112.5s */
	long ltime;
	/* Time in seconds */
	long sec;

	/* DS18b20 temperature in decicelsius */
	int16_t t1;
	/* DS18B20 result status */
	char ds_status;

	/*
	 * Control variables
	 */
	/* t1 setpoint */
	int16_t t1_sp;
	/* Control mode */
	enum ctrl_mode_t ctrl_mode;
} status_t;


/* Settings storage adresses */
#define EEPROM_T1 0

#endif

