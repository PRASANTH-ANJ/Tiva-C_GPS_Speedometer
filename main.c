#include "uart.h"
#include "timer.h"


//uint32_t  count;
uint16_t count;

char rcvdata[100];

/* 
 * Function : main
 *
 * Description : Send a string via UART0 to the terminal program in a pc with the configuration below
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
 	
 	/* Initialize the UART0 module */
 	uartInit();
 	
 	stringSend("Initialization completed \n");
 	
 	stringSend("waiting for receiving....\n");
 	
 	while(1)
 	{
 	
 		//stringReceive(rcvdata, &count);
 		
 		//stringSend(rcvdata);
 		
 		stringReceive(rcvdata, &count, '$', '*');
 		
 		stringSend("Received string is : ");
 		
 		stringSend(rcvdata);
 		
 		stringSend("\n");
 		
 	}
 	
 	return 0;
 	
 }
