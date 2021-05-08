#include "uart.h"
#include "timer.h"
#include "gps.h"
#include "nmea.h"
#include <math.h>


uint16_t count;

/* Global variables to recieve data */
char rcvdata[200], time[10], speed[4], validity[2], latitude[15], ns[2], longitude[15], ew[2];// longitude[15];

/* 
 * Function : main
 *
 * Description : Get the NMEA string from GPS module and extract its fields using different functions to
 *		store each field in separate character arrays. Then send the array string to 
 *		pc using following configuration:
 *			9600, 8, N, 1
 *
 * Notes : Uses the uart driver specific to the TM4C1294NCPDT Controller.
 *		UART0 : interface with PC
 *		UART7 : Interface with GPS module (Cirocomm 600L)
 *
 * Returns : Contains an infinite loop 
 */
 
 int main (void)
 {	
 		
 	/* Initialize the timer module for delay_ms function */
 	timerInit();
 	
 	/* Initialize the UART0 */
 	uartInit();
 	
 	/* Initialize the GPS module connected to UART7 */
 	gpsInit();
 	
 	/* Commanding the GPS module to send only GPGGA and GPVTG sentenses */
 	gpsSend("$PMTK314,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0*28\r\n");
 	
 	/* Receive the acknowledge string PMTK001 */
 	nmeaReceive(rcvdata, 1, '$', '*');
 	
 	/* Send the ACK string to pc with a line feed */
 	stringSend(rcvdata);
 	stringSend("\n");
 	
 	stringSend("Initialization completed \n");
 	
 	stringSend("waiting for GPS data....\n");
 	
 	while(1)
 	{
 		/* Receive the required NMEA sentenses from GPS */
 		nmeaReceive(rcvdata, 2, '$', '*');

		/* Get the validity field value in 'validity' array. '0' -> Invalid fix */
 		getField(validity, VALIDITY_INDEX);
 		
 		/* Checking whether the fix is valid or not */
 		if((validity[0] == '1') || (validity[0] == '2'))
 		{
			/* Get the local time stored in the 'time' array
			   and send it to the pc */
			getlocalTime();
						
			/* Get the Latitude value stored in the 'latitude' array
			   and send it to the pc */
			getLatitude();
			
			/* Get the Longitude value stored in the 'longitude' array
			   and send it to the pc */
			getLongitude();
			
			/* Get the speed in Km/h stored in the 'speed' array
			   and send it to the pc */
			getSpeed();
			
			stringSend("\n");
 			
 		}
 		
 		/* Current fix is not valid */
 		else
 		{
 			stringSend("No GPS fix found.....");
 			
	 		stringSend("\n");
 		}
		
 	}
 	
 	return 0;
 	
 }
