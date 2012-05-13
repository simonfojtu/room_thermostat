/*
 * @Author  : Simon Fojtu
 * @Date    : 19.06.2011
 */

#ifndef __HW_H_
#define __HW_H_

#include "defs.h"

void hw_init(void);
void hw_read_tick(status_t * stat);
void hw_write_tick(status_t * stat);


#endif

