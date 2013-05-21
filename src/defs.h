/*
 * @Author  : Simon Fojtu
 * @Date    : 13.05.2011
 */

#ifndef __DEFS_H_
#define __DEFS_H_

#include <stdint.h>

#ifndef NULL
#define NULL 0
#endif

#include "fsm.h"

/* Uart communication speed */
#define BAUDRATE 9600
/* Events queue buffer size */
#define EVENTS_QUEUE_MAX_SIZE 8

#define KBD_EVT_QUEUE_SIZE 10
// how many ticks must a button be held down to be considered 'pressed'
#define BUTTON_HELD_TIMEOUT 12

#define PROG_ENTRIES_COUNT 5

/* DS18B20 status */
#define DS_OK		0
#define DS_READ_ERROR	1
#define DS_MEAS_ERROR	2

enum ctrl_mode_t {
	CTRL_OFF,
        CTRL_HYST,
	CTRL_MAX
};

enum event_type {
	EVENT_B_UP,
	EVENT_B_DOWN,
	EVENT_B_MENU,
        EVENT_B_HELD,
	EVENT_NOP,
	MAX_EVENTS
};

enum fsm_state_t {
        FSM_SP,
        FSM_MIN,
        FSM_HOUR,
        FSM_MODE,
        FSM_PROG,
        FSM_MAX
};

/*
 * Keyboard UI
 */

typedef struct KbdEvent KbdEvent;
struct KbdEvent {
	Event super_;
	char code;
};

typedef struct KbdEvtQueue KbdEvtQueue;
struct KbdEvtQueue {
	int size;
	KbdEvent queue[KBD_EVT_QUEUE_SIZE];
};

typedef struct ProgEntry ProgEntry;
struct ProgEntry {
        int16_t temp;
        int16_t min;
};

/*
 * Structure to hold device status
 */
typedef struct Context Context;
struct Context {
	Fsm fsm;
        /* Keyboard FSM */
        KbdEvtQueue kbdEvtQueue;
        enum fsm_state_t fsm_state;

	/* Time in minutes */
	volatile int16_t min;

        /* time offset in minutes */
        int16_t t_offset;

	/* temperature in decicelsius */
	int16_t t1;
	/* temperature status */
	char temp_status;

	/*
	 * Control variables
	 */
	/* t1 setpoint */
	int16_t t1_sp;
	/* Control mode */
	enum ctrl_mode_t ctrl_mode;

        /*
         * Program - setpoints and times
         */
        ProgEntry progEntries[PROG_ENTRIES_COUNT];
        uint8_t entry_id;
        uint8_t thm;
};


/* Settings storage adresses */
#define EEPROM_T1 0 // dword = 4 bytes

#define EEPROM_PE 4 // PROG_ENTRY_COUNT * (int16_t + int16_t)


#endif

