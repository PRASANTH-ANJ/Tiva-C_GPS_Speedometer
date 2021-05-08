#include "nmea.h"
#include <string.h>
#include "uart.h"

int getField(char * value, char field)
{
	uint16_t i = 0, j = 0, count = 0;
	
	char head[] = "GPGGA";
	
	if(strncmp(head, rcvdata, 5))
	{
		return 1;
	}
	
	for( ; count < field; i++)
	{
	
		if(rcvdata[i] == ',')
		{
		
			count++;
		
		}
		
		else if(rcvdata[i] == '\0')
		{
		
			value[0] = '\0';
			
			return 1;
		
		}
	
	}
	
	while(rcvdata[i] != ',')
	{
	
		value[j] = rcvdata[i];
		
		j++;
		
		i++;
	
	}
	
	value[j] = '\0';
	
	return 0;
	
}





void getlocalTime(void)
{
	
	uint8_t hh, mm, ss, temp;
	
	char localtime[10];
	
	if(!getField(time, TIME_INDEX))
	{
		
		temp = ((time[2] - '0') * 10) + (time[3] - '0') + 30;
		
		mm = temp % 60;
	
		hh = ((time[0] - '0') * 10) + (time[1] - '0') + 5 + (temp / 60);
	
		ss = ((time[4] - '0') * 10) + (time[5] - '0');
		
		if(hh >=24)
		{
		
			hh = 0;
		
		}
		
		if(hh < 10)
		{
		
			localtime[0] = '0';
			
			localtime[1] = (hh % 10) + '0';
		
		}
		
		else
		{
			
			localtime[0] = (hh / 10) + '0';
			
			localtime[1] = (hh % 10) + '0';
		
		}
		
		localtime[2] = ':';
		
		if(mm < 10)
		{
		
			localtime[3] = '0';
			
			localtime[4] = (mm % 10) + '0';
		
		}
		
		else
		{
			
			localtime[3] = (mm / 10) + '0';
			
			localtime[4] = (mm % 10) + '0';
		
		}
		
		localtime[5] = ':';
		
		if(ss < 10)
		{
		
			localtime[6] = '0';
			
			localtime[7] = (ss % 10) + '0';
		
		}
		
		else
		{
			
			localtime[6] = (ss / 10) + '0';
			
			localtime[7] = (ss % 10) + '0';
		
		}
		
		localtime[8] = '\0';
		
		stringSend(localtime);
		
		stringSend(" ");
		
	}	
		
}


void getSpeed(void)
{
	if(!getField(speed, SPEED_INDEX))
	{
		
		stringSend(speed);
		
		stringSend(" Km/h ");
		
	}
}



void getLatitude(void)
{
	char latstring[15];
	
	int deg, min;
	
	//float templat, tempmin;
	
	uint16_t sec;
	
	getField(ns, 3);
	
	if(!getField(latitude, LATITUDE_INDEX))
	{
		
		deg =  ((latitude[0] - '0') * 10) + (latitude[1] - '0');
		
		min = ((latitude[2] - '0') * 10) + (latitude[3] - '0');
		
		sec = ((latitude[5] - '0') * 1000) + ((latitude[6] - '0') * 100) + ((latitude[7] - '0') * 10) + (latitude[8] - '0');
		
		/*
		
		
		
		tempmin = (float)((float)(min + (float)(sec/10000))/60);
		
		templat = (float)(deg + tempmin);
		
		deg = (int)templat;
		
		tempmin = (float)(templat - deg);
		
		min = tempmin * 1000000;
		
		
		
		
		
		
		latstring[0] = (deg / 10) + '0';
		
		latstring[1] = (deg % 10) + '0';
		
		latstring[2] = '.';
		
		latstring[3] = (min / 100000) + '0';
		
		min = min % 100000;
		
		latstring[4] = (min / 10000) + '0';
		
		min = min % 10000;
		
		latstring[5] = (min / 1000) + '0';
		
		min = min % 1000;
		
		latstring[6] = (min / 100) + '0';
		
		min = min % 100;
		
		latstring[7] = (min / 10) + '0';
		
		latstring[8] = (min % 10) + '0';
		
		*/
		
		latstring[0] = (deg / 10) + '0';
		
		latstring[1] = (deg % 10) + '0';
		
		latstring[2] = 'd'; 
		
		latstring[3] = (min / 10) + '0';
		
		latstring[4] = (min % 10) + '0';
		
		latstring[5] = (char)0x2E;
		
		latstring[6] = (sec / 1000) + '0';
		
		sec = sec % 1000;
		
		latstring[7] = (sec / 100) + '0';
		
		sec = sec % 100;
		
		latstring[8] = (sec / 10) + '0';
		
		latstring[9] = (sec % 10) + '0';
		
		latstring[10] = 'm';
		
		latstring[11] = ' ';
		
		latstring[12] = ns[0] ;
		
		latstring[13] = '\0';
		
		stringSend(latstring);
		
		stringSend(" ");
		
	}
}




void getLongitude(void)
{
	char lonstring[16];
	
	int deg, min;
	
	//float templat, tempmin;
	
	uint16_t sec;
	
	getField(ew, 5);
	
	if(!getField(longitude, LONGITUDE_INDEX))
	{
		
		deg =  ((longitude[0] - '0') * 100) + ((longitude[1] - '0') * 10) + (longitude[2] - '0');
		
		min = ((longitude[3] - '0') * 10) + (longitude[4] - '0');
		
		sec = ((longitude[6] - '0') * 1000) + ((longitude[7] - '0') * 100) + ((longitude[8] - '0') * 10) + (longitude[9] - '0');
		
		/*
		
		
		
		tempmin = (float)((float)(min + (float)(sec/10000))/60);
		
		templat = (float)(deg + tempmin);
		
		deg = (int)templat;
		
		tempmin = (float)(templat - deg);
		
		min = tempmin * 1000000;
		
		
		
		
		
		
		latstring[0] = (deg / 10) + '0';
		
		latstring[1] = (deg % 10) + '0';
		
		latstring[2] = '.';
		
		latstring[3] = (min / 100000) + '0';
		
		min = min % 100000;
		
		latstring[4] = (min / 10000) + '0';
		
		min = min % 10000;
		
		latstring[5] = (min / 1000) + '0';
		
		min = min % 1000;
		
		latstring[6] = (min / 100) + '0';
		
		min = min % 100;
		
		latstring[7] = (min / 10) + '0';
		
		latstring[8] = (min % 10) + '0';
		
		*/
		
		lonstring[0] = (deg / 100) + '0';
		
		deg = (deg % 100);
		
		lonstring[1] = (deg /10) + '0';
		
		lonstring[2] = (deg % 10) + '0';
		
		lonstring[3] = 'd'; 
		
		lonstring[4] = (min / 10) + '0';
		
		lonstring[5] = (min % 10) + '0';
		
		lonstring[6] = (char)0x2E;
		
		lonstring[7] = (sec / 1000) + '0';
		
		sec = sec % 1000;
		
		lonstring[8] = (sec / 100) + '0';
		
		sec = sec % 100;
		
		lonstring[9] = (sec / 10) + '0';
		
		lonstring[10] = (sec % 10) + '0';
		
		lonstring[11] = 'm';
		
		lonstring[12] = ' ';
		
		lonstring[13] = ew[0] ;
		
		lonstring[14] = '\0';
		
		stringSend(lonstring);
		
		stringSend(" ");
		
	}
}



