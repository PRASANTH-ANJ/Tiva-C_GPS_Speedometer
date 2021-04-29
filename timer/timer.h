#ifndef __TIMER_H__
#define __TIMER_H__

#include <stdint.h>
#include "tm4c1294ncpdt.h"

#define TIMER0_CLKEN 1
#define TIMER0_CLKDBLE 0
#define TIMER0_DISABLE 0XFFFFFEFE
#define TIMER0_ENABLE 0X01
#define TIMER0_TIMEOUT 0X01
#define ONESHOT_MODE 0x01
#define COUNT_UP 0x10
#define ONE_MILLISECOND_COUNT 0x3E01

void timerInit(void);
void delay_ms(uint32_t milliseconds);

#endif
