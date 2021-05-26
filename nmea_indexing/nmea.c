#include "nmea.h"
#include <string.h>
#include "uart.h"
#include "ssd1306.h"
#include "ugui.h"



/*
 * Function : getField
 *
 * Description : Extract a field from the stored array of NMEA sentenses ('rcvdata')
 *		by counting the comas in the string.
 *			
 * Parameters : 
 *		value -> pointer to the storage array
 *
 *		field -> index of required field. See 'nmea.h' macro defenitions for field values.
 *
 * Notes : This function is specific to the TM4C1294NCPDT controller.
 *	   If the overflow of GPS UART happens, case-1 or case-2 will be considered.
 *
 * Returns : None
 */

int getField(char * value, char field)
{
	uint16_t i = 0, j = 0, count = 0;
	
	char head[] = "GPGGA";
	
	/* case-1 : Checking whether the stored nmea string starts with expected header or not. */
	if(strncmp(head, rcvdata, 5))
	{
		/* Something went wrong. Terminate the function */
		return 1;
	}
	
	/* Counting the ',' character in the string to correctly index to the field */
	for( ; count < field; i++)
	{
	
		if(rcvdata[i] == ',')
		{
		
			count++;
		
		}
		
		/* case-2 : String contains null in an unexpected area,
		   either due to an invalid field index or due to GPS UART receiver error */
		else if(rcvdata[i] == '\0')
		{
		
			value[0] = '\0';
			
			/* Something went wrong. Terminate the function */
			return 1;
		
		}
	
	}
	
	/* Starting of the requird field found. Now extract the filed characters */
	while(rcvdata[i] != ',')
	{
		
		/* Storing each character in to the array*/
		value[j] = rcvdata[i];
		
		j++;
		
		i++;
	
	}
	
	value[j] = '\0';
	
	return 0;
	
}





/*
 * Function : getlocalTime
 *
 * Description : Extract the UTC time from NMEA sentense. Then convert it in to 
 *		local time (+5:30 here), before storing in to the respective array.
 *			
 * Parameters : None
 *
 * Notes : This function is specific to the TM4C1294NCPDT controller.
 *
 * Returns : None
 */

void getlocalTime(void)
{
	
	uint8_t hh, mm, ss, temp;
	
	char localtime[10];
	
	/* Extract the UTC time field values */
	if(!getField(time, TIME_INDEX))
	{
		
		/* Convert the characters to numbers for localtime calculation */
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
		
		/* Send it to the pc */
		//stringSend(localtime);
		
		//stringSend(" ");
		
		UG_PutString(0, 0, localtime);
	
		//display(display_buffer);
		
	}
	else
	{
		
		/* Error occured*/
		localtime[0] = '\0';
		
	}
		
		
}





/*
 * Function : getSpeed
 *
 * Description : Extract the speed in Kmph from NMEA sentense. Then store it and send to pc. 
 *			
 * Parameters : None
 *
 * Notes : This function is specific to the TM4C1294NCPDT controller.
 *
 * Returns : None
 */

void getSpeed(void)
{
	/* Extract speed data */
	if(!getField(speed, SPEED_INDEX))
	{
		
		//stringSend(speed);
		
		//stringSend(" Km/h ");
		
		UG_PutString(72, 0, speed);
		
		UG_PutString(104, 0, "Km");
	
		//display(display_buffer);
		
	}
	else
	{
		
		/* Error occured*/
		speed[0] = '\0';
		
	}
}




/*
 * Function : getLatitude
 *
 * Description : Extract the Latitude data from NMEA sentense. Then store it and send to pc. 
 *			
 * Parameters : None
 *
 * Notes : This function is specific to the TM4C1294NCPDT controller.
 *
 * Returns : None
 */

void getLatitude(void)
{
	char latstring[15];
	
	/* Get the N/S character from the gps data */
	getField(ns, N_S_INDEX);
	
	/* Get the Latitude data */
	if(!getField(latitude, LATITUDE_INDEX))
	{
		/* Formating the string for display */
		latstring[0] = latitude[0];
		
		latstring[1] = latitude[1];
		
		latstring[2] = 'd'; 
		
		latstring[3] = latitude[2];
		
		latstring[4] = latitude[3];
		
		latstring[5] = (char)0x2E;
		
		latstring[6] = latitude[5];
		
		latstring[7] = latitude[6];
		
		latstring[8] = latitude[7];
		
		latstring[9] = latitude[8];
		
		latstring[10] = 'm';
		
		latstring[11] = ' ';
		
		latstring[12] = ns[0] ;
		
		latstring[13] = '\0';
		
		//stringSend(latstring);
		
		//stringSend(" ");
		
		UG_PutString(0, 12, latstring);
	
		//display(display_buffer);
		
	}
	else
	{
		
		/* Error occured*/
		latitude[0] = '\0';
		
		latstring[0] = '\0';
		
	}
	
}






/*
 * Function : getLongitude
 *
 * Description : Extract the Longitude data from NMEA sentense. Then store it and send to pc. 
 *			
 * Parameters : None
 *
 * Notes : This function is specific to the TM4C1294NCPDT controller.
 *
 * Returns : None
 */

void getLongitude(void)
{
	char lonstring[16];
	
	/* Get the E/W character */
	getField(ew, E_W_INDEX);
	
	if(!getField(longitude, LONGITUDE_INDEX))
	{
	
		lonstring[0] = longitude[0];
		
		lonstring[1] = longitude[1];
		
		lonstring[2] = longitude[2];
		
		lonstring[3] = 'd'; 
		
		lonstring[4] = longitude[3];
		
		lonstring[5] = longitude[4];
		
		lonstring[6] = (char)0x2E;
		
		lonstring[7] = longitude[6];
		
		lonstring[8] = longitude[7];
		
		lonstring[9] = longitude[8];
		
		lonstring[10] = longitude[9];
		
		lonstring[11] = 'm';
		
		lonstring[12] = ' ';
		
		lonstring[13] = ew[0] ;
		
		lonstring[14] = '\0';
		
		//stringSend(lonstring);
		
		//stringSend(" ");
		
		UG_PutString(0, 24, lonstring);
	
		//display(display_buffer);
		
	}
	else
	{
		/* Error occured*/
		longitude[0] = '\0';
		
		lonstring[0] = '\0';
		
	}
	
}



