#ifndef __UART_H__
#define __UART_H__

#include <stdint.h>
#include "tm4c1294ncpdt.h"

/* Macro defines*/
#define UART0_ENABLE 0x00000001
#define EN_PORTA 0x00000001
#define PA0 0x01
#define PA1 0x02
#define ASSIGN_UART0 0x00000011
#define EN_UART 0x01
#define DIS_UART 0x00
#define BUSY_FLAG 0x0000008

void uartInit(void);

void uartSend(char);

#endif
