#include "uart.h"
#include "timer.h"
#include "gps.h"


//uint32_t  count;
uint16_t count;

char rcvdata[200];

/* 
 * Function : main
 *
 * Description : Get and store the NMEA string from GPS to a char ayyay and
 *		  sent the array string to the pc with the configuration below
 *			9600, 8, N, 1
 *
 * Notes : Uses the uart driver specific to the TM4C1294NCPDT Controller
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
 		
		stringSend(rcvdata);
		
 		stringSend("\n");
 	
 	}
 	
 	return 0;
 	
 }
