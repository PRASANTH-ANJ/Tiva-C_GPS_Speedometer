#ifndef __NMEA_H__
#define __NMEA_H__

#include <stdint.h>

/* Macro defenitions */
#define SPEED_INDEX 21
#define TIME_INDEX 1
#define LATITUDE_INDEX 2
#define N_S_INDEX 3
#define LONGITUDE_INDEX 4
#define E_W_INDEX 5
#define VALIDITY_INDEX 6

/* Global variables in main for storage of extracted fields */
extern char rcvdata[200], time[10], speed[4], latitude[15], ns[2], longitude[15], ew[2];

/* Functions for field indexing and extraction*/
int getField(char * , char );

void getlocalTime(void);

void getSpeed(void);

void getLatitude(void);

void getLongitude(void);


#endif
