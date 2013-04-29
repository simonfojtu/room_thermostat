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

void gui_display_(Context *ctx);

extern unsigned char char_start; // defined in 3310_routines.c

void gui_tick(Context * ctx)
{
	gui_display_(ctx);
}

void gui_display_(Context * ctx)
{
	int hour;
        static Context ctx_prev;

	// TODO display selection

	/* DS18B20 sensor output */
        if ((ctx->t1 != ctx_prev.t1) || (ctx->temp_status != ctx_prev.temp_status) || (ctx->t1_sp != ctx_prev.t1_sp)) {
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
//	        	LCD_writeString_F((unsigned char *) "err");
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
        }

	/* current time */
	if (ctx->min != min_ || ctx->min != ctx_prev.min || ctx_prev.t_offset != ctx->t_offset) {
                int min = ctx->min + ctx->t_offset;
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
	}


	/* display mode on/off */
        if (ctx->ctrl_mode != ctx_prev.ctrl_mode) {
        	LCD_gotoXY(64,1);
        	switch (ctx->ctrl_mode) {
        	case(CTRL_HYST):
        		LCD_writeChar(SMALL_FONT_SPACE);
        		LCD_writeChar(SMALL_FONT_SPACE);
        		LCD_writeChar(SMALL_FONT_SPACE);
        		break;
        	case(CTRL_OFF):
        		LCD_writeChar(SMALL_FONT_o);
        		LCD_writeChar(SMALL_FONT_f);
        		LCD_writeChar(SMALL_FONT_f);
        		break;
                case(CTRL_MAX):
                        // to keep compiler quiet about not handling CTRL_MAX in the switch
                        break;
        	}
        }

        // store context
        ctx_prev = *ctx;
}


