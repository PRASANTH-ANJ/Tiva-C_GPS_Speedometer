#ifndef __NMEA_H__
#define __NMEA_H__

#include <stdint.h>

#define SPEED_INDEX 21
#define TIME_INDEX 1
#define LATITUDE_INDEX 2
#define LONGITUDE_INDEX 4
#define VALIDITY_INDEX 6

extern char rcvdata[200], time[10], speed[4], latitude[15], ns[2], longitude[15], ew[2];

int getField(char * , char );

void getlocalTime(void);

void getSpeed(void);

void getLatitude(void);

void getLongitude(void);


#endif
