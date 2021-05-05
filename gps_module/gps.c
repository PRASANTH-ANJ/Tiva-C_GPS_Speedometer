#include "gps.h"
#include "uart.h"
#include <string.h>

/*
 * Function : gpsInit
 *
 * Description : Initialize the gps module connected to the UART7 module with the following spec:
 *			9600 baud rate
 *			8 data bits
 *			No parity bits
 *			One stop bit
 *			Clocked from default 16MHz PIOSC
 *
 * Notes : This function is specific to the TM4C1294NCPDT controller.
 *
 * Returns : None
 */
 
 void gpsInit(void)
 {
 
 	/****************************** Port Configuration ******************************/
 	
 	/* Enable clock to the UART7 module */
 	SYSCTL_RCGCUART_R |= UART7_ENABLE;	
 	
 	/* Enable clock to the Port C GPIO module, connected to the UART7 signals */
 	SYSCTL_RCGCGPIO_R |= EN_PORTC;
 	
 	/* Set GPIOAFSEL for Port C to enable the alternate functions on pins 4 and 5 */
 	GPIO_PORTC_AHB_AFSEL_R |= (PC5 | PC4);
 	
 	/* Set the slewrate and current level for the pins PC4 and PC5*/
 	/* Since there is no specific information, we enable 8mA drive for the pins 
 	   and the slewrate is kept untouched*/
 	GPIO_PORTC_AHB_DR8R_R |= (PC5 | PC4);
 	
 	/* Select the peripheral signal to be assigned to the pins PC4 and PC5 */
 	GPIO_PORTC_AHB_PCTL_R = (GPIO_PORTC_AHB_PCTL_R & 0xFF00FFFF) | ASSIGN_UART7;
 	
	/* Enable digital functions on the selected pins PC4 and PC5 */
 	GPIO_PORTC_AHB_DEN_R |= (PC5 | PC4);
 	
 	
 	/****************************** UART-7Configuration ******************************
 		Baud-rate	:	9600
 		Data length	:	8-bits 
 		Parity		:	None
 		Stop bits	:	1
 		FIFO status	:	Enabled
 		Interrupts	: 	Disabled
 	*/
 	
 	/* Disable UART module before any configuration */
 	UART7_CTL_R |= DIS_UART;
 	
 	/* Write integer portion of Baud-Rate Divisor */
 	UART7_IBRD_R = 0x68; // refer to baud rate divisor calculation equation on page 1165. 
 	
 	/* Write fractional portion of BRD */
 	UART7_FBRD_R = 0x2B; // refer to baud rate divisor calculation equation on page 1165.
 	
 	/* Configure the desired serial parameters 
 			8-bits data length
 			FIFO enabled */
 	UART7_LCRH_R |= 0x00000070;
 	
 	/* Enable UART */
 	UART7_CTL_R |= EN_UART;
 	
 }
 




/*
 * Function : gpsReceive
 *
 * Description : Receive a character from the GPS through UART7
 *
 * Notes : This function is specific to the TM4C1294NCPDT controller.
 *
 * Returns : The byte data received
 */
 
 
 char gpsReceive(void)
 {
 	/* Temporary storage variable for received data along with 4 error status bits */
 	uint16_t temp;
 	
 	/* Variable for extracted data field from 'temp'*/
 	char cdata;
 	
	while(UART7_FR_R & RXFEMPTY);
 	
 	temp = UART7_DR_R;
 	
 	if(temp & OVERRUN_ERROR)
 	{
 		stringSend("Overrun Error Occured!\n");
 	}
 	
 	if(temp & BREAK_ERROR)
 	{
 		stringSend("Break Error occured!\n");
 	}
 	
 	if(temp & FRAME_ERROR)
 	{
 		stringSend("Frame Error occured!\n");
 	}
 	
 	/* Clear the error flags by writing to error clear register*/
 	UART7_ECR_R = 0;
 	
 	/* Extract the data field */ 	
 	cdata = temp & DATA_BITS;
 	
 	return cdata;

 }
 



/*
 * Function : gpsSend
 *
 * Description : Send a string (command) to the GPS module through UART7
 *
 * Parameters : 
 *		strdata -> string to be send
 *
 * Notes : This function is specific to the TM4C1294NCPDT controller.
 *
 * Returns : The byte data received
 */
 
 void gpsSend(char * strdata)
{

	uint16_t i;
	
	for(i=0; i<strlen(strdata); i++)
	{

		/* Place the data to be transmitted in the data register */
		UART7_DR_R = strdata[i];	
		
		/* Wait here if the FIFO is full */
		while(UART7_FR_R & TXFFULL);
		
	}
	
	/* check for transmission complete */
	while(UART7_FR_R & BUSY_FLAG);

}




/*
 * Function : nmeaReceive
 *
 * Description : Receive 'count' number of nmea sentenses from the GPS module
 *		 through UART7 and store it as a string in the 'str_data' array
 *		 for later use.
 *			
 * Parameters : 
 *		str_data -> pointer to the storage array
 *		count -> Number of nmea sentenses to be stored to the array
 *		header -> nmea header ('$' in this case)
 *		footer -> nmea footer ('*' in this case)
 *
 * Notes : In the stored string, a '#' is used to separate the nmea sentenses.
 *	   This function is specific to the TM4C1294NCPDT controller.
 *
 * Returns : The byte data received
 */


void nmeaReceive(char str_data[], char count, char header, char footer)
 {
 	uint16_t temp, i = 0, j;
 	
 	/* Clear the error flags by writing to error clear register*/
	UART7_ECR_R = 0;
 	
 	while(count>0)
 	{
 		/* Wait until FIFO is empty */
 		while(UART7_FR_R & RXFEMPTY);
 		
 		/* Check for the header ($) */
 		while((UART7_DR_R & DATA_BITS) != header);
 		
 		/* Wait until FIFO is empty. This checking is required since the controller
 		   executes faster than the UART reception */
 		while(UART7_FR_R & RXFEMPTY);
 		
 		/* Read data from FIFO */
 		temp = UART7_DR_R;
 		
 		/* Receive and make string till the received character is not footer (*) */
 		while((temp & DATA_BITS) != footer)
 		{
 			/* Store data to the array */
 			str_data[i] = (temp & DATA_BITS);
 		 	
 		 	/* Increment character counter */	
 			i++;
 			
 			/* Check for any receiver error. If any terminate the function and clear the array */
 			if(temp & (OVERRUN_ERROR | BREAK_ERROR | FRAME_ERROR))
 			{
 		 			
 				if(temp & OVERRUN_ERROR)
 				{
			 		stringSend("GPS Overrun Error Occured!\n");
			 	}
 	
			 	if(temp & BREAK_ERROR)
			 	{
			 		stringSend("GPS Break Error occured!\n");
			 	}
 	
			 	if(temp & FRAME_ERROR)
			 	{
			 		stringSend("GPS Frame Error occured!\n");
			 	}
		 	
			 	/* Clear the error flags by writing to error clear register*/
 				UART7_ECR_R = 0;
 				
 				/* Clear the array */
 				str_data[0] = '\0';
 				
 				/* Terminating the function */
 				count = 0;
		 	
			 	break;
 			}
 		
 			while(UART7_FR_R & RXFEMPTY);
 		
 			temp = UART7_DR_R;
 		
 		}
 		
 		/* Sentense counter */
 		count--;
 		
 	}
 	
 	/* This section is used to fill zeros to the tail of the aray
 	   during any length changes of the string takes place */
 	j = i + 5;
 	while(i <= j)
 	{
 		str_data[i++] = ' ';
 	}
 	
 	/* Don't forget to put a null character at the end of the string */
 	str_data[i] = '\0';
 	
 }


 
 
