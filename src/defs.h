/*
 * @Author  : Simon Fojtu
 * @Date    : 13.05.2011
 */

#ifndef __DEFS_H_
#define __DEFS_H_

#include "fsm.h"

#ifndef NULL
#define NULL 0
#endif

/*
 * Pinout settings
 */

/* USI (SPI) */
#define USIMOSI PB3
#define USIMOSIDDR DDRB
#define USIMISO PB4
#define USIMISODDR DDRB
#define USISCK PB5
#define USISCKDDR DDRB
#define USISS PC7
#define USISSDDR DDRC 

/* Display control */
#define INIT_DISPLAY_PINS       do {DDRB |= (1 << PB0); DDRC |= (1 << PC3); DDRD |= (1 << PD5);} while (0)
#define SET_DC_PIN              PORTB |= 1 << PB0
#define CLEAR_DC_PIN            PORTB &= ~(1 << PB0)
#define SET_SCE_PIN             PORTD |= 1 << PD5
#define CLEAR_SCE_PIN           PORTD &= ~(1 << PD5)
#define SET_RST_PIN             PORTC |= 1 << PC3
#define CLEAR_RST_PIN           PORTC &= ~(1 << PC3)

/* Buttons */
#define INIT_BUTTONS_PINS       do {DDRC |= (1 << PC0) | (1 << PC1) | (1 << PC2);} while (0)
/* TODO Check ui logic (up above down, ...) */
#define UP_PRESSED              ((PINC & 1<<PC0) == 0)
#define DOWN_PRESSED            ((PINC & 1<<PC1) == 0)
#define MODE_PRESSED            ((PINC & 1<<PC2) == 0)

/* Action output */
#define SET_CTRL_PIN            PORTC |= 1 << PC5
#define CLEAR_CTRL_PIN          PORTC &= ~(1 << PC5)
#define INIT_CTRL_PINS          do {DDRC |= (1 << PC5);} while (0)

/* DS18B20, OW pin */
#define OW_PIN  PC4
#define OW_IN   PINC
#define OW_OUT  PORTC
#define OW_DDR  DDRC


/*
 * Functional settings
 */

/* Uart communication speed */
#define BAUDRATE 9600

/* Events queue buffer size */
#define KBD_EVT_QUEUE_SIZE 4

/* DS18B20 status */
#define DS_OK		0
#define DS_READ_ERROR	1
#define DS_MEAS_ERROR	2

/*
 * Types
 */

typedef signed int int16_t;

enum ctrl_mode_t {
        CTRL_OFF,
        CTRL_MAN,
        CTRL_AUTO,
        CTRL_MAX
};

/* Structure to hold device status */
typedef struct {
        /* Time in 1/TIMER0_OVF_FREQ s */
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

#endif

