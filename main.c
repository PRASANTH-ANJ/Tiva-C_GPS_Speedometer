#include "uart.h"
#include "timer.h"

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
 	while(1)
 	{
 	
 		/* Transmit a character to the serial port of pc */
 		uartSend('p');
 	
	 	/* Wait for a small delay */
 		delay_ms(1000);
 		
 	}
 	
 	return 0;
 	
 }
