/*
 * @Author  : Simon Fojtu
 * @Date    : 19.06.2011
 */

#include "gui.h"

//#include <stdlib.h>

/* Nokia 3310 LCD */
#include "3310_routines.h"
/* SPI */
#include "spi.h"


int min_ = -1;

extern unsigned char char_start; // defined in 3310_routines.c

void gui_tick(Context * ctx)
{
	uint8_t hour;
        static Context ctx_prev;

	// TODO display selection
        
        if ((ctx->fsm_state != ctx_prev.fsm_state) && ((ctx->fsm_state == FSM_PROG) || (ctx_prev.fsm_state == FSM_PROG)))
                LCD_clear();

	/* DS18B20 sensor output */
        if (ctx->fsm_state != FSM_PROG) {
                int16_t tmp;
                LCD_gotoXY(0, 0);
                if (ctx->temp_status == DS_OK) {
                        char_start = 0;
                        tmp = ctx->t1;
                        if (tmp/100 == 0)
                                char_start+=12;
                        else
                                LCD_writeChar_megaFont(tmp/100);
                        tmp -= (tmp/100)*100;
                        LCD_writeChar_megaFont(tmp/10);
                        tmp -= (tmp/10)*10;
                	LCD_writeChar_megaFont(MEGA_FONT_DOT);
                        LCD_writeChar_megaFont(tmp);
                        LCD_gotoXY(char_start, 1);
                        LCD_writeChar(SMALL_FONT_CIRC);
                        LCD_writeChar(SMALL_FONT_C);
                } else {
                	LCD_writeString_F((unsigned char *) "err");
                }
        
                // Temperature setpoint
                LCD_gotoXY(57, 0);
                tmp = ctx->t1_sp;
                if (tmp/100 == 0)
                        LCD_writeChar(SMALL_FONT_SPACE);
                else
                        LCD_writeChar(tmp/100);
                tmp -= (tmp/100)*100;
                LCD_writeChar(tmp/10);
                tmp -= (tmp/10)*10;
                LCD_writeChar(SMALL_FONT_DOT);
                LCD_writeChar(tmp);
        
                /* current time */
                int16_t min = ctx->min + ctx->t_offset;
        	hour = (min / 60) % 24;
        	min = (min - hour * 60) % 60;
        
        	LCD_gotoXY(0, 3);
                LCD_writeChar(hour / 10);
                LCD_writeChar(hour % 10);
        	LCD_writeChar(SMALL_FONT_COLON);
                LCD_writeChar(min / 10);
                LCD_writeChar(min % 10);
        	LCD_writeChar(SMALL_FONT_SPACE);
        	LCD_writeChar(SMALL_FONT_SPACE);
        
        
                /* display mode on/off */
        	LCD_gotoXY(64,1);
        	switch (ctx->ctrl_mode) {
        	case(CTRL_OFF):
        		LCD_writeChar(SMALL_FONT_o);
        		LCD_writeChar(SMALL_FONT_f);
        		LCD_writeChar(SMALL_FONT_f);
        		break;
        	case(CTRL_HYST):
        		LCD_writeChar(SMALL_FONT_SPACE);
        		LCD_writeChar(SMALL_FONT_SPACE);
        		LCD_writeChar(SMALL_FONT_SPACE);
        		break;
                case(CTRL_AUTO):
                        LCD_writeChar(SMALL_FONT_a);
        		LCD_writeChar(SMALL_FONT_SPACE);
        		LCD_writeChar(SMALL_FONT_SPACE);
                        break;
                case(CTRL_MAX):
                        // to keep compiler quiet about not handling CTRL_MAX in the switch
                        break;
        	}
        } else { // FSM_PROG
                for (uint8_t i = 0; i < PROG_ENTRIES_COUNT; i++) {
                        int16_t tmp, min;
                        int8_t hour;

        		LCD_gotoXY(0, i);
                        if (ctx->entry_id == i)
                                LCD_writeChar(SMALL_FONT_COLON);
                        else
                                LCD_writeChar(SMALL_FONT_SPACE);

                        tmp = ctx->progEntries[i].temp;

                        LCD_writeChar(tmp/100);
                        tmp -= (tmp/100)*100;
                        LCD_writeChar(tmp/10);
                        tmp -= (tmp/10)*10;
        	        LCD_writeChar(SMALL_FONT_DOT);
                        LCD_writeChar(tmp);
                        LCD_writeChar(SMALL_FONT_C);
        		LCD_writeChar(SMALL_FONT_SPACE);

                        min = ctx->progEntries[i].min;
        		hour = min / 60;
        		min = min - hour * 60;
        
                        LCD_writeChar(hour / 10);
                        LCD_writeChar(hour % 10);
        		LCD_writeChar(SMALL_FONT_COLON);
                        LCD_writeChar(min / 10);
                        LCD_writeChar(min % 10);
                }
        }

        // store context
        ctx_prev = *ctx;
}


