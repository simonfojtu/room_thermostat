/*
 * @Author  : Simon Fojtu
 * @Date    : 19.06.2011
 */

#include "gui.h"

#include <stdlib.h>

/* Nokia 3310 LCD */
#include "3310_routines.h"
/* SPI */
#include "spi.h"


long sec_ = -1;

void gui_display_(Context *ctx);

void gui_tick(Context * ctx)
{
	gui_display_(ctx);
}

void gui_display_(Context * ctx)
{
	long hour;
	long min;
	char buffer[15];
        Context ctx_prev;

	// TODO display selection

	/* DS18B20 sensor output */
        if ((ctx->t1 != ctx_prev.t1) || (ctx->ds_status != ctx_prev.ds_status) || (ctx->t1_sp != ctx_prev.t1_sp)) {
	        LCD_gotoXY(0, 1);
	        if (ctx->ds_status == DS_OK) {
	        	LCD_writeString_F((unsigned char *) ltoa(ctx->t1/10, buffer, 10));
	        	LCD_writeChar('.');
	        	LCD_writeString_F((unsigned char *) ltoa(ctx->t1- (ctx->t1/10)*10, buffer, 10));
	        } else {
	        	LCD_writeString_F((unsigned char *) "err");
	        }
	        LCD_writeChar(' ');
	        LCD_writeChar('(');
	        LCD_writeString_F((unsigned char *) ltoa(ctx->t1_sp/10, buffer, 10));
	        LCD_writeChar('.');
	        LCD_writeString_F((unsigned char *) ltoa(ctx->t1_sp - (ctx->t1_sp/10)*10, buffer, 10));
	        LCD_writeChar(')');
	        LCD_writeChar(' ');
        }

	/* current time */
	if (ctx->sec != sec_) {
		hour = (ctx->sec / 3600) % 24;
		min = ctx->sec / 60 - hour * 60;
		sec_ = ctx->sec - hour * 3600 - min * 60;

		LCD_gotoXY(0, 3);
		LCD_writeString_F((unsigned char *) ltoa(hour, buffer, 10));
		LCD_writeChar(':');
		if (min < 10)
			LCD_writeChar('0');
		LCD_writeString_F((unsigned char *) ltoa(min, buffer, 10));
		LCD_writeChar(':');
		if (sec_ < 10)
			LCD_writeChar('0');
		LCD_writeString_F((unsigned char *) ltoa(sec_, buffer, 10));
		LCD_writeChar(' ');
		LCD_writeChar(' ');
	}


	/* display mode */
        if (ctx->ctrl_mode != ctx_prev.ctrl_mode) {
        	LCD_gotoXY(0,4);
        	switch (ctx->ctrl_mode) {
        	case(CTRL_HYST):
        		LCD_writeChar(' ');
        		LCD_writeChar(' ');
        		LCD_writeChar(' ');
        		break;
        	case(CTRL_OFF):
        		LCD_writeChar('o');
        		LCD_writeChar('f');
        		LCD_writeChar('f');
        		break;
                case(CTRL_MAX):
                        // to keep compiler quiet about not handling CTRL_MAX in the switch
                        break;
        	}
        }

        // store context
        ctx_prev = *ctx;
}


