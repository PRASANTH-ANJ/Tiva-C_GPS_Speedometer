#ifndef __GPS_H__
#define __GPS_H__

#include <stdint.h>
#include <string.h>
#include "tm4c1294ncpdt.h"

/* Macro defines*/
#define UART7_ENABLE 0x00000080
#define EN_PORTC 0x00000004
#define PC4 0x10
#define PC5 0x20
#define ASSIGN_UART7 0x00110000
#define EN_UART 0x01
#define DIS_UART 0x00
#define BUSY_FLAG 0x0000008
#define OVERRUN_ERROR 0x00000800
#define BREAK_ERROR 0x00000400
#define PARITY_ERROR 0x00000200
#define FRAME_ERROR 0x00000100
#define DATA_BITS 0x000000FF
#define RXFFULL 0x00000040
#define RXFEMPTY 0x00000010
#define TXFFULL 0x00000020

// $PMTK314,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0*28\r\n

void gpsInit(void);

char gpsReceive(void);

void gpsSend(char * strdata);

void nmeaReceive(char str_data[], char count, char header, char footer);

#endif
